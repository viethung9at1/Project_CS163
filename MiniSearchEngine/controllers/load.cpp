#include "../models/SearchEngine.h"
#include "../models/dirent.h"
#include<fstream>
#include<filesystem>
//#include<dirent.h>
namespace fs = std::filesystem;
using std::ifstream, std::cout, std::endl;
int numOfWord = 0;
void SearchEngine::loadData() { // Load files, stopwords
	DIR* dir;
	struct dirent* ent;
	int numberOfFile = 0;
	cout << "Loading - [" << string(100, '=') << ']';
	if ((dir = opendir("DataSearch")) != NULL) {
		int i = 0;
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_name[0] == '.') continue;
			//if (++numberOfFile > 2000) break;
			filenames.push_back(ent->d_name);

			if (numberOfFile % 20 == 0) {
				gotoXY(10 + numberOfFile / 20, 0);
				cout << (char)254;
			}

			//load file
			data[ent->d_name] = NULL;
			loadFile(data[ent->d_name], ent->d_name);
			//cout << ent->d_name << endl;
		}
		cout << i;
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
				if (s[i] != '\t') addToSyn += s[i];
				if (i == s.length() - 1 || s[i] == '\t') {
					syn.push_back(addToSyn);
					synoMap[addToSyn] = synoList.size();
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
	int i = 0, line = 0;
	string inputAllLine;
	while (!fin.eof()) {
		getline(fin, inputAllLine);

		string s;
		for (int k = 0; k < inputAllLine.length(); k++) {
			if (inputAllLine[k] != ' ') s += inputAllLine[k];
			if (k == (int)inputAllLine.length() - 1 || inputAllLine[k] == ' ') {
				if (s.empty()) continue;
				if (s[s.length() - 1] == '.') s.erase(s.size() - 1);
				root->insert(s, i++, line == 0 ? true : false);
				s = "";
			}
		}
		line++;
	}

	fileLength[filename] = i;
}
