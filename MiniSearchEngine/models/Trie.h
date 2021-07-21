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
	void insert(string key, int occur, bool isTitle);
	vector<int> search(string key, bool isTitle);
	vector<int> searchRange(TrieNode* node, float left, float right, string key = "");
	vector<int> combineOccurs(vector<int> occur1, vector<int> occur2);
	int convert(char key);
};

#endif