#ifndef SEARCH_ENGINE
#define SEARCH_ENGINE

#include "Trie.h"
#include "console.h"
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <conio.h>
#include <Windows.h>
using namespace std;

struct result {
	string filename;
	vector<int> occur;
	int point;

	/* OPERATOR */
	bool operator< (result b);
};

class SearchEngine {
	map<string, TrieNode*> data;
	TrieNode* stopWords;

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
	vector<result> searchQuery(string text);
};

#endif
