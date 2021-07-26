#ifndef SEARCH_ENGINE
#define SEARCH_ENGINE

#include "Trie.h"
#include "console.h"
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>

using std::set,std::map,std::vector;

struct result {
	string filename;
	vector<int> occurs;
	int point;

	/* OPERATOR */
	bool operator< (result b);

	/* CONSTRUCTOR */
	result(string filename, vector<int> occurs, int totalOperator);
};

class SearchEngine {
private:
	map<string, TrieNode*> data;
	TrieNode* stopWords;

	vector<string> filenames;
	map<string, int> fileLength;

	map<string, int> synoMap;
	vector< vector<string> > synoList;
public:
	// load.cpp
	void loadData(); // Load files, stopwords
	void loadFile(TrieNode*& root, string filename);

	// interface.cpp
	void run();
	void drawGoogle(int x, int y);
	void suggest(int coor, string data);

	vector<string> getSuggestion(vector<string>history, string text);// Online History
	void readInput(vector<string>& history, string& text, int x, int y, bool& stop);
	void drawFrame(int a, int b);
	void draw(int x, int y);

	// engine.cpp
	string upperCase(string key);
	bool isStopWord(string key);
	bool getRange(string word, string& left, string& right);
	vector<int> exactCombineOccurs(vector<int> occur1, vector<int> occur2);
	vector<int> fillMatch(vector<int> exactSearch, int numberOfWord);
	vector<result> searchQuery(string text);
	result searchQuery(string filename, string text);

	void showResult(string text, vector<result> results);
	void showResultList(int x, int y, vector<result> results);
	void printDescription(int x, int y, int maxLength, result Result);
	void printContent(result Result);
};

#endif
