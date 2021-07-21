#include "../models/Trie.h"

TrieNode::TrieNode() {
	isWord = isTitle = false;
	for (int i = 0; i < 42; ++i) child[i] = NULL;
}
void TrieNode::insert(string key, int occur, bool isTitle) {
	TrieNode* node = this;
	int n = key.size();
	for (int i = 0; i < n; ++i) {
		int c = convert(key[i]);
		if (c == -1) continue;
		if (!node->child[c]) node->child[c] = new TrieNode();
		node = node->child[c];
	}
	node->isWord = true;
	node->isTitle |= isTitle;
	node->occurs.push_back(occur);
}
vector<int> TrieNode::search(string key, bool isTitle) {
	TrieNode* node = this;
	int n = key.size();
	bool empty = true;
	for (int i = 0; i < n; ++i) {
		int c = convert(key[i]);
		if (c == -1) continue;
		empty = false;
		if (!node->child[c]) return vector<int>();
		node = node->child[c];
	}
	if (empty) return vector<int>(1, -1); // empty key, still valid search
	return node->isWord && (node->isTitle || !isTitle) ? node->occurs : vector<int>(); // empty search, not found key
}
vector<int> TrieNode::searchRange(TrieNode* node, float left, float right, string key) {
	if (node->isWord) {
		float num = atof(key.c_str());
		if (left < num && num < right)
			return node->occurs;
	}
	vector<int> results;
	for (int i = 0; i < 11; ++i) {
		char c = i < 10 ? '0' + i : '.';
		if (node->child[i]) results = combineOccurs(
			results, 
			searchRange(node->child[i], left, right, key + c)
		);
	}
	return results;
}
int TrieNode::convert(char key) {
	if ('0' <= key && key <= '9') return key - '0';
	if ('a' <= key && key <= 'z') return key - 'a' + 11;
	if ('A' <= key && key <= 'Z') return key - 'A' + 11;
	switch (key) {
		case '.': return 10;
		case ' ': return 37;
		case '$': return 38;
		case '%': return 39;
		case '#': return 40;
		case '-': return 41;
	}
	return -1;
}
vector<int> TrieNode::combineOccurs(vector<int> occur1, vector<int> occur2) {
	if (occur1.size() == 0) return occur2;
	if (occur2.size() == 0) return occur1;
	vector<int> occurs; int i = 0, j = 0;
	while (i < occur1.size() || j < occur2.size()) {
		while (j == occur2.size() || (i < occur1.size() && j < occur2.size() && occur1[i] < occur2[j])) occurs.push_back(occur1[i++]);
		while (i == occur1.size() || (i < occur1.size() && j < occur2.size() && occur1[i] > occur2[j])) occurs.push_back(occur2[j++]);
		while (i < occur1.size() && j < occur2.size() && occur1[i] == occur2[j]) occurs.push_back(occur1[i]), i++, j++;
	}
	return occurs;
}