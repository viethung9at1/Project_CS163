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
TrieNode* TrieNode::search(string key, bool isTitle) {
	TrieNode* node = this;
	int n = key.size();
	for (int i = 0; i < n; ++i) {
		int c = convert(key[i]);
		if (c == -1) continue;
		if (!node->child[c]) return NULL;
		node = node->child[c];
	}
	return node->isWord && (node->isTitle || !isTitle) ? node : NULL;
}
int TrieNode::convert(char key) {
	if ('0' <= key && key <= '9') return key - '0';
	if ('a' <= key && key <= 'z') return key - 'a' + 10;
	if ('A' <= key && key <= 'Z') return key - 'A' + 10;
	switch (key) {
		case ' ': return 36;
		case '.': return 37;
		case '$': return 38;
		case '%': return 39;
		case '#': return 40;
		case '-': return 41;
	}
	return -1;
}
vector<int> combine(vector<int> occur1, vector<int> occur2) {
	return vector<int>();
}