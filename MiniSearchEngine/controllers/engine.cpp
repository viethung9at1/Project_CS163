#include "../models/SearchEngine.h"

result::result(string filename, vector<int> occurs) : filename(filename), occurs(occurs) {
}
bool result::operator< (result b) {
	return occurs.size() > b.occurs.size() || (occurs.size() == b.occurs.size() && filename < b.filename);
}
bool SearchEngine::isStopWord(string key) {
	return stopWords->search(key, 0);
}
vector<int> SearchEngine::combineOccurs(vector<int> occur1, vector<int> occur2) {
	vector<int> occurs; int i = 0, j = 0;
	while (i < occur1.size() || j < occur2.size()) {
		while (j == occur2.size() || (i < occur1.size() && j < occur2.size() && occur1[i] < occur2[j])) occurs.push_back(occur1[i++]);
		while (i == occur1.size() || (i < occur1.size() && j < occur2.size() && occur1[i] > occur2[j])) occurs.push_back(occur2[j++]);
		while (i < occur1.size() && j < occur2.size() && occur1[i] == occur2[j]) occurs.push_back(occur1[i]), i++, j++;
	}
	return occurs;
}
vector<result> SearchEngine::searchQuery(string text) {
	vector<result> results;
	for (string filename : filenames) {
		vector<int> search = searchQuery(filename, text);
		if (search.size()) results.push_back(result(filename, search));
	}
	sort(results.begin(), results.end());
	return results;
}
vector<int> SearchEngine::searchQuery(string filename, string text) {
	return vector<int>();
}