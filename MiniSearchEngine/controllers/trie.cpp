#include "../models/Trie.h"

TrieNode::TrieNode() {
	isWord = isTitle = false;
	for (int i = 0; i < 42; ++i) child[i] = NULL;
}
void TrieNode::insert(string key, int occur, bool isTitle, bool isStopWord) {

}
void TrieNode::search(string key, bool isTitle) {

}
int convert(char key) {
	return -1;
}
vector<int> combine(vector<int> occur1, vector<int> occur2) {

}