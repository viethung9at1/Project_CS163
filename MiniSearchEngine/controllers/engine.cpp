#include "../models/SearchEngine.h"
#include <fstream>
using namespace std;

result::result(string filename, vector<int> occurs, int totalOperator) : filename(filename), occurs(occurs) {
	point = occurs.size() + totalOperator * 100000;
	for (int i = 0; i + 1  < occurs.size(); ++i)
		point += (occurs[i] + 1 == occurs[i + 1]);
}
bool result::operator< (result b) {
	return point > b.point || (point == b.point && filename < b.filename);
}
bool SearchEngine::isStopWord(string key) {
	return (stopWords->search(key, 0)).size();
}
bool SearchEngine::getRange(string word, string left, string right) {
	int dots = 0;
	while (dots + 1 < word.size() && (word[dots] != '.' || word[dots + 1] != '.')) dots += 1;

	if (dots + 1 < word.size()) {
		left = word.substr(0, dots);
		right = word.substr(dots + 2);
		if (!left.size() || !right.size()) return false;
		if (left[0] == '$' && right[0] != '$') right = '$' + right;
		if (left[0] != '$' && right[0] == '$') left = '$' + left;
	}
	else left = right = word;

	return true;
}
vector<int> SearchEngine::exactCombineOccurs(vector<int> occur1, vector<int> occur2) {
	if (occur1.empty() || occur2.empty()) return occur2;
	vector<int> occurs;
	for (int i = 0, j = 0; i < occur2.size(); ++i) {
		while (j < occur1.size() && occur1[j] < occur2[i] - 1) j += 1;
		if (occur1[j] == occur2[i] - 1) occurs.push_back(occur2[i]);
	}
	return occurs;
}
vector<int> SearchEngine::fillMatch(vector<int> exactSearch, int numberOfWord) {
	vector<int> occurs;
	for (int occur : exactSearch)
		for (int i = 0; i < numberOfWord; ++i)
			occurs.push_back(occur - i);
	sort(occurs.begin(), occurs.end());
	occurs.resize(distance(occurs.begin(), unique(occurs.begin(), occurs.end())));
	return occurs;
}
vector<result> SearchEngine::searchQuery(string text) {
	vector<result> results;
	for (string filename : filenames) {
		int i = 0;
		result search = searchQuery(filename, text);
		while (i < results.size() && results[i] < search) i = i + 1;

		results.push_back(search);
		for (int j = (int)results.size() - 1; j > i; --j) swap(results[j], results[j - 1]);
		if (results.size() > 5) results.pop_back();
	}
	return results;
}
result SearchEngine::searchQuery(string filename, string text) {
	stringstream query(text);
	string word;
	vector<int> results, search;
	int totalOperator = 0;
	int prePlaceHolds = 0;
	bool lastSearch = true;
	bool AND = false, OR = false;

	while (query >> word) {
		if (word == "AND") {
			AND = lastSearch;
			OR = false;
		}
		else if (word == "OR") {
			OR = !lastSearch;
			AND = false;
			totalOperator += lastSearch;
		}
		else if (word[0] == '-') { // strictly check 
			word = word.substr(1);
			search = data[filename]->search(word, false);

			lastSearch = false;
			if (!search.size() || search[0] == -1) {
				totalOperator += 1 + AND + OR;
				lastSearch = true;
			}
			AND = OR = false;
		}
		else if (word.substr(0, 8) == "intitle:") { // strictly check
			word = word.substr(8);
			search = data[filename]->search(word, true);

			if (search.size()) {
				results = combineOccurs(results, search);
				totalOperator += 1 + AND + OR;
			}
			lastSearch = search.size() > 0;
			AND = OR = false;
		}
		else if (word[0] == '+' || word[0] == '#') { // strictly check
			search = data[filename]->search(word, false);

			if (search.size()) {
				results = combineOccurs(results, search);
				totalOperator += 1 + AND + OR;
			}
			lastSearch = search.size() > 0;
			AND = OR = false;
		}
		else if (word.substr(0, 9) == "filetype:") { // strictly check
			word = word.substr(9);

			lastSearch = false;
			if (filename.substr(filename.size() - word.size()) == word) {
				totalOperator += 1 + AND + OR;
				lastSearch = true;
			}
			AND = OR = false;
		}
		else if (('0' <= word[0] && word[0] <= '9') || word[0] == '$') { // strictly check
			string left, right;
			if (!getRange(word, left, right)) {
				lastSearch = AND = OR = false;
				continue;
			}
			search = left[0] != '$' ?
				searchRange(data[filename], atof(left.c_str()), atof(right.c_str())) :
				searchRange(data[filename]->child[convert('$')], atof(left.c_str()), atof(right.c_str()));

			if (search.size()) {
				results = combineOccurs(results, search);
				totalOperator += 1 + AND + OR;
			}
			lastSearch = search.size() > 0;
			AND = OR = false;
		}
		else if (word[0] == '\"') { // strictly check
			vector<int> exactSearch; 
			int numberOfWord = 0;
			do {
				if (word == "*" || word == "\"*" || word == "*\"" || word == "\"*\"") {
					for (int& occur : exactSearch) occur = occur + 1;
					if (!exactSearch.empty() && exactSearch.back() >= fileLength[filename])
						exactSearch.pop_back();
				}
				else {
					search = data[filename]->search(word, false);
					exactSearch = exactCombineOccurs(exactSearch, search);
				}
				numberOfWord += 1;
				if (word.back() == '\"' || !exactSearch.size()) break;
			} while (query >> word);

			if (exactSearch.size()) {
				search = fillMatch(exactSearch, numberOfWord);
				results = combineOccurs(results, search);
				totalOperator += 2 + AND + OR;
			}
			lastSearch = exactSearch.size() > 0;
			AND = OR = false;
		}
		else if (word == "*") { // non-strictly check
			if (!results.size()) {
				prePlaceHolds += 1;
				continue;
			}

			vector<int> placeHolds = results;
			for (int& occur : placeHolds) occur += 1;
			if (!placeHolds.empty() && placeHolds.back() == fileLength[filename]) 
				placeHolds.pop_back();

			results = combineOccurs(results, placeHolds);
			totalOperator += AND + OR;
			lastSearch = true;
			AND = OR = false;
		}
		else if (word[0] == '~') { // non-strictly check
			lastSearch = false;
			word = word.substr(1);
			if (!synoMap.count(word)) continue;
			for (string syno : synoList[synoMap[word]]) {
				search = data[filename]->search(syno, false);
				results = combineOccurs(results, search);
				lastSearch |= search.size() > 0;
			}

			if (lastSearch) totalOperator += AND + OR;
			AND = OR = false;
		}
		else { // non-strictly check
			if (isStopWord(word)) continue;
			search = data[filename]->search(word, false);

			results = combineOccurs(results, search);
			if (search.size()) totalOperator += AND + OR;
			lastSearch = search.size() > 0;
			AND = OR = false;
		}
	}

	if (prePlaceHolds > 0) results = fillMatch(results, prePlaceHolds);
	
	return result(filename, results, totalOperator);
}
void SearchEngine::showRawResult(vector<result> results) {
	system("CLS");
	for (result x : results) printResult(x);
	while (_getch() != 27);
}
void SearchEngine::printResult(result Result) {
	string filename = Result.filename;
	vector<int> occurs = Result.occurs;

	cout << filename << ' ' << occurs.size() << '\n';

	ifstream fin;
	fin.open("DataSearch\\" + filename);
	if (!fin) {
		cout << '\n';
		// cout << "Cannot open file " + filename << endl;
		return;
	}
	int i = 0, iOccur = 0;
	string inputAllLine;
	while (!fin.eof()) {
		getline(fin, inputAllLine);
		string s;
		if (true) {
			for (int k = 0; k < inputAllLine.length(); k++) {
				if (inputAllLine[k] != ' ') s += inputAllLine[k];
				if (k == (int)inputAllLine.length() - 1 || inputAllLine[k] == ' ') {
					if (s.empty()) continue;
					// if (s[s.length() - 1] == '.') s.erase(s.size() - 1);
					// root->insert(s, i++, line == 0 ? true : false);
					if (iOccur < occurs.size() && occurs[iOccur] == i) {
						TextColor(ColorCode_Yellow);
						cout << s << ' ';
						TextColor(default_ColorCode);
						iOccur += 1;
					}
					else cout << s << ' ';
					
					s = ""; i = i + 1;
				}
			}
		}
		cout << '\n';
	}
	cout << '\n';
}