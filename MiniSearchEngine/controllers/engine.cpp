#include "../models/SearchEngine.h"

result::result(string filename, vector<int> occurs) : filename(filename), occurs(occurs) {
}
bool result::operator< (result b) {
	return occurs.size() > b.occurs.size() || (occurs.size() == b.occurs.size() && filename < b.filename);
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
		result search = result(filename, searchQuery(filename, text));
		while (i < results.size() && results[i] < search) i = i + 1;

		results.push_back(search);
		for (int j = results.size() - 1; j > i; --j) swap(results[j], results[j - 1]);
		if (results.size() > 5) results.pop_back();
	}
	return results;
}
vector<int> SearchEngine::searchQuery(string filename, string text) {
	stringstream query(text);
	string word;
	vector<int> results, search, NONE = vector<int>();

	while (query >> word) {
		if (word[0] == '-') { // strictly check 
			word = word.substr(1);
			search = data[filename]->search(word, false);
			if (search.size() && search[0] != -1 && !isStopWord(word)) return NONE;
		}
		else if (word.substr(0, 8) == "intitle:") { // strictly check
			word = word.substr(8);
			search = data[filename]->search(word, true);
			if (!search.size() && !isStopWord(word)) return NONE;
			results = combineOccurs(results, search);
		}
		else if (word[0] == '+' || word[0] == '#') { // strictly check
			search = data[filename]->search(word, false);
			if (!search.size()) return NONE;
			results = combineOccurs(results, search);
		}
		else if (word.substr(0, 9) == "filetype:") { // strictly check
			word = word.substr(9);
			if (filename.substr(filename.size() - word.size()) != word) return NONE;
		}
		else if (('0' <= word[0] && word[0] <= '9') || word[0] == '#') { // strictly check
			string left, right;
			if (!getRange(word, left, right)) continue;
			search = left[0] == '$' ?
				searchRange(data[filename], atof(left.c_str()), atof(right.c_str())) :
				searchRange(data[filename]->child[convert('$')], atof(left.c_str()), atof(right.c_str()));
			if (!search.size()) return NONE;
			results = combineOccurs(results, search);
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
				if (!exactSearch.size()) return NONE;

				numberOfWord += 1;
				if (word.back() == '\"') break;
			} while (query >> word);

			search = exactMatch(exactSearch, numberOfWord);
			results = combineOccurs(results, search);
		}
		else if (word == "*") { // non-strictly check
			vector<int> placeHolds = results;
			for (int& occur : placeHolds) occur += 1;
			if (!placeHolds.empty() && placeHolds.back() == fileLength[filename]) 
				placeHolds.pop_back();
			results = combineOccurs(results, placeHolds);
		}
		else if (word[0] == '~') { // non-strictly check
			word = word.substr(1);
			if (isStopWord(word)) continue;
			if (!synoMap.count(word)) continue;
			vector<string> synonyms = synoList[synoMap[word]];
			for (string syno : synonyms) {
				search = data[filename]->search(syno, false);
				results = combineOccurs(results, search);
			}
		}
		else { // non-strictly check
			if (isStopWord(word)) continue;
			search = data[filename]->search(word, false);
			results = combineOccurs(results, search);
		}
	}
	return results;
}