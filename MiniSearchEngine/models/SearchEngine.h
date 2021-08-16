#ifndef SEARCH_ENGINE
#define SEARCH_ENGINE

#include "Trie.h"
#include "console.h"
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <sstream>
#define TOP_LEFT 201
#define TOP_RIGHT 187
#define BOT_LEFT 200
#define BOT_RIGHT 188
#define VERTICAL 186
#define HORIZONTAL 205
#define SPACE 32

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define TOP_LEFT_lite 218
#define TOP_RIGHT_lite 191
#define BOT_LEFT_lite 192
#define BOT_RIGHT_lite 217
#define VERTICAL_lite 179
#define HORIZONTAL_lite 196
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
	void loadSyno();
	void loadStopword();
	void saveTrie(TrieNode*& root, string filename);
	TrieNode* loadTrie(string filename);

	// interface.cpp
	void run();
	void drawGoogle(int x, int y);
	void suggest(int coor, string data);

	vector<string> getSuggestion(vector<string>history, string text);// Online History
	void readInput(vector<string>& history, string& text, int x, int y, bool& stop);
	void drawFrame(int a, int b,int w);
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
