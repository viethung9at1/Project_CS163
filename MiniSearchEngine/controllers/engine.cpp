#include "../models/SearchEngine.h"

result::result(string filename, vector<int> occurs) : filename(filename), occurs(occurs) {
}
bool result::operator< (result b) {
	return occurs.size() > b.occurs.size() || (occurs.size() == b.occurs.size() && filename < b.filename);
}
bool SearchEngine::isStopWord(string key) {
	return (stopWords->search(key, 0)).size();
}
vector<result> SearchEngine::searchQuery(string text) {
	vector<result> results;
	for (string filename : filenames) {
		result search = result(filename, searchQuery(filename, text));

		int i = 0;
		while (i < results.size() && results[i] < search) i = i + 1;

		results.push_back(search);
		for (int j = results.size() - 1; j > i; --j) swap(results[j], results[j - 1]);
		if (results.size() > 5) results.pop_back();
	}
	return results;
}
vector<int> SearchEngine::searchQuery(string filename, string text) {
	return vector<int>();
}