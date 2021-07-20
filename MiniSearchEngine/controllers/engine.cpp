#include "../models/SearchEngine.h"

bool result::operator< (result b) {
	return occurs.size() < b.occurs.size();
}
vector<result> SearchEngine::searchQuery(string text) {
	return vector<result>();
}
bool SearchEngine::isStopWord(string key) {
	return stopWords->search(key, 0);
}
vector<int> SearchEngine::combineOccurs(vector<int> occur1, vector<int> occur2) {
	if (!occur2.size()) return occur1;
	for (int i : occur1) if (occur2[0] == i) return occur1;
	vector<int> occurs(occur1.size() + occur2.size());
	occurs.insert(occurs.end(), occur1.begin(), occur1.end());
	occurs.insert(occurs.end(), occur2.begin(), occur2.end());
	return occurs;
}