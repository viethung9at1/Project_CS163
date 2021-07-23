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
			getline(fin, s);
			for (int i = 0; i < s.length(); i++) {
				if (s[i] != ' ') addToSyn += s[i];
				if (i == s.length() - 1 || s[i] == ' ') {
					syn.push_back(addToSyn);
					synoMap[syn[0]]=synoList.size();
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
	ifstream fin;
	fin.open("DataSearch\\" + filename);
	if (!fin) {
		cout << "Cannot open file " + filename << endl;
		return;
	}
	int i = 0;
	string s;
	while (!fin.eof()&&s!="") {
		fin >> s;
		if (s[s.length() - 1] == '.' || s[s.length() - 1] == ',')
			s.replace(s.length() - 1, 1, "");
		if (s.length() > 2 && s.substr(0, 1) == "\"") 
			s.replace(0, 1, "");
		if (s.length() > 2 && s.substr(s.length() - 1, 1) == "\"") 
			s.replace(s.length() - 1, 1, "");
		root->insert(s, i++, i == 0 ? true : false);
	}
	fileLength[filename] = i;
	fin.close();
}
