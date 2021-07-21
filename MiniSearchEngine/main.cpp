#include<iostream>
#include "models/SearchEngine.h"

using namespace std;

int main()
{
	SearchEngine Google;
	// Google.loadData();
	// Google.run();
	vector<result> results = Google.searchQuery("steve jobs");

	TrieNode* root = new TrieNode();
	root->insert("abcd", 2, 1);
	root->insert("abcd", 8, 0);
	root->insert("abc", 10, 0);

	TrieNode* find = root->search("abcd", 0);
	if (find) {
		for (int i : find->occurs)
			cout << i << ' ';
		cout << '\n';
	}
	else cout << "not found\n";

	system("pause");
}