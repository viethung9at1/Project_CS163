#ifndef TRIE_DATA_STRUCTURE
#define TRIE_DATA_SRTUCTURE

#include <iostream>
#include <vector>
using namespace std;

struct TrieNode {
	TrieNode* child[42]; // 0-9:number, 10-35:a-z, 36:':', 37:'.', 38:'$', 39:'%', 40:'#', 41:'-'
	bool isWord, isTitle;
	vector<int> occurs;

	/* CONSTRUCTOR */
	TrieNode();

	/* METHODS */
	void insert(string key, int occur, bool isTitle, bool isStopWord);
	void search(string key, bool isTitle);
};

int convert(char key);
vector<int> combine(vector<int> occur1, vector<int> occur2);

#endif