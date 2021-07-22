#include "../models/SearchEngine.h"
using namespace std;
result::result(string filename, vector<int> occurs, int totalOperator) : filename(filename), occurs(occurs) {
	point = occurs.size() + totalOperator * 100000;
	for (int i = 0; i < occurs.size() - 1; ++i)
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
vector<int> SearchEngine::exactMatch(vector<int> exactSearch, int numberOfWord) {
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
		for (int j = results.size() - 1; j > i; --j) swap(results[j], results[j - 1]);
		if (results.size() > 5) results.pop_back();
	}
	return results;
}
result SearchEngine::searchQuery(string filename, string text) {
	stringstream query(text);
	string word;
	vector<int> results, search;
	int totalOperator = 0;
	bool lastSearch = true;
	bool AND = false, OR = false;

	while (query >> word) {
		if (word == "AND") {
			AND = lastSearch;
		}
		else if (word == "OR") {
			OR = !lastSearch;
			if (lastSearch) totalOperator += 1;
		}
		else if (word[0] == '-') { // strictly check 
			lastSearch = false;
			word = word.substr(1);
			search = data[filename]->search(word, false);
			if (search.size() && search[0] != -1) continue;
			totalOperator += 1 + AND + OR;
			AND = OR = false;
			lastSearch = true;
		}
		else if (word.substr(0, 8) == "intitle:") { // strictly check
			lastSearch = false;
			word = word.substr(8);
			search = data[filename]->search(word, true);
			if (!search.size()) continue;
			results = combineOccurs(results, search);
			totalOperator += 1 + AND + OR;
			AND = OR = false;
			lastSearch = true;
		}
		else if (word[0] == '+' || word[0] == '#') { // strictly check
			lastSearch = false;
			search = data[filename]->search(word, false);
			if (!search.size()) continue;
			results = combineOccurs(results, search);
			totalOperator += 1 + AND + OR;
			AND = OR = false;
			lastSearch = true;
		}
		else if (word.substr(0, 9) == "filetype:") { // strictly check
			lastSearch = false;
			word = word.substr(9);
			if (filename.substr(filename.size() - word.size()) != word) continue;
			totalOperator += 1 + AND + OR;
			AND = OR = false;
			lastSearch = true;
		}
		else if (('0' <= word[0] && word[0] <= '9') || word[0] == '$') { // strictly check
			lastSearch = false;
			string left, right;
			if (!getRange(word, left, right)) continue;
			search = left[0] != '$' ?
				searchRange(data[filename], atof(left.c_str()), atof(right.c_str())) :
				searchRange(data[filename]->child[convert('$')], atof(left.c_str()), atof(right.c_str()));
			if (!search.size()) continue;
			results = combineOccurs(results, search);
			totalOperator += 1 + AND + OR;
			AND = OR = false;
			lastSearch = true;
		}
		else if (word[0] == '\"') { // strictly check
			lastSearch = false;
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
				if (!exactSearch.size()) break;

				numberOfWord += 1;
				if (word.back() == '\"') break;
			} while (query >> word);

			if (!exactSearch.size()) continue;
			search = exactMatch(exactSearch, numberOfWord);
			results = combineOccurs(results, search);
			totalOperator += 2 + AND + OR;
			AND = OR = false;
			lastSearch = true;
		}
		else if (word == "*") { // non-strictly check
			vector<int> placeHolds = results;
			for (int& occur : placeHolds) occur += 1;
			if (!placeHolds.empty() && placeHolds.back() == fileLength[filename]) 
				placeHolds.pop_back();
			results = combineOccurs(results, placeHolds);
			totalOperator += AND + OR;
			AND = OR = false;
			lastSearch = true;
		}
		else if (word[0] == '~') { // non-strictly check
			bool found = false;
			word = word.substr(1);
			if (isStopWord(word)) continue;
			if (!synoMap.count(word)) continue;
			for (string syno : synoList[synoMap[word]]) {
				search = data[filename]->search(syno, false);
				if (search.size()) found = true;
				results = combineOccurs(results, search);
			}
			if (found) totalOperator += AND + OR;
			AND = OR = false;
			lastSearch = found;
		}
		else { // non-strictly check
			if (isStopWord(word)) continue;
			search = data[filename]->search(word, false);
			results = combineOccurs(results, search);
			if (search.size()) totalOperator += AND + OR;
			AND = OR = false;
			lastSearch = search.size() > 0;
		}
	}
	
	return result(filename, results, totalOperator);
}