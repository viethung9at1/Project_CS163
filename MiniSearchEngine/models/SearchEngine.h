#ifndef SEARCH_ENGINE
#define SEARCH_ENGINE

#include "Trie.h"
#include "console.h"
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct result {
	string filename;
	vector<int> occurs;
	int point;

	/* OPERATOR */
	bool operator< (result b);

	/* CONSTRUCTOR */
	result(string filename, vector<int> occurs);
};

class SearchEngine {
	map<string, TrieNode*> data;
	TrieNode* stopWords;
	vector<string> filenames;
public:
	// load.cpp
	void loadData(); // Load files, stopwords
	void loadFile(TrieNode* root, string filename);

	// interface.cpp
	void run();
	void drawGoogle(int x, int y);
	void suggest(int coor, string data);

	vector<string> getSuggestion(vector<string>history, string text);// Online History
	void readInput(vector<string>& history, string& text, int x, int y, bool& stop);
	void drawFrame(int a, int b);
	void draw(int x, int y);

	//set<string> getWords(string text);

	void showResult(vector<result> results, string text, set<string> words);
	vector<string> getReview(string filename, set<string> words, int maxLength);
	vector<string> getContent(string filename, int maxLength);

	// engine.cpp
	bool isStopWord(string key);
	vector<int> combineOccurs(vector<int> occur1, vector<int> occur2);
	vector<result> searchQuery(string text);
	vector<int> searchQuery(string filename, string text);
};

#endif