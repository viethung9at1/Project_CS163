#include "../models/SearchEngine.h"
#include<fstream>
#include<dirent.h>
using namespace std;
void SearchEngine::loadData() { // Load files, stopwords
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir("DataSearch")) != NULL) {
		while ((ent = readdir(dir)) != NULL)
		{
			filenames.push_back(ent->d_name);

			//load file
			data[ent->d_name] = NULL;
			loadFile(data[ent->d_name], ent->d_name);
		}
		closedir(dir);
	}
	ifstream fin;
	fin.open("synonyms.txt");
	if (fin) {
		while (!fin.eof()) {
			string s, addToSyn = "";
			vector<string> syn;
			getline(fin,s);
			for (int i = 0; i < s.length(); i++) {
				if(s[i]!=' ') addToSyn += s[i];
				else {
					syn.push_back(addToSyn);
					synoMap[syn[0]]++;
					addToSyn = "";
				}
			}
			synoList.push_back(syn);
		}
	}
	fin.close();
	fin.open("stopwords.txt");
	stopWords = new TrieNode();
	if (fin) {
		int i = 0;
		while (!fin.eof()) {
			string s;
			fin >> s;
			stopWords->insert(s, i++, i == 0 ? true : false);
		}
	}
	fin.close();
}
void SearchEngine::loadFile(TrieNode*& root, string filename) {
	root = new TrieNode();

}
