#include "../models/SearchEngine.h"
#include "../models/dirent.h"
#include<fstream>
//#include<dirent.h>
using namespace std;

void SearchEngine::reload() {
	DIR* dir; struct dirent* ent;
	int numberOfFile = 0, totalFile = 0, scale, totalLoad = 0;
	set<string> loaded;

	system("CLS");
	cout << "Loading - [" << string(100, '=') << ']';

	if ((dir = opendir("Loaded")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] == '.') continue;
			string filename = ent->d_name;
			filename = filename.substr(0, filename.size() - 4);
			loaded.insert(filename);
		}
		closedir(dir);
	}

	if ((dir = opendir("DataSearch")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] == '.') continue;
			totalFile += 1;
		}
		closedir(dir);
	}
	totalLoad = totalFile - loaded.size();
	scale = totalFile / 100;
	if (scale == 0) {
		scale = 1;
		numberOfFile = 100 - totalLoad;
		for (int i = 0; i < numberOfFile; ++i) {
			gotoXY(10 + i, 0);
			cout << (char)254;
		}
	}

	if ((dir = opendir("DataSearch")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string filename = ent->d_name;
			if (filename[0] == '.') continue;

			if (!loaded.count(filename)) {
				TrieNode* root = new TrieNode();
				loadFile(root, filename);
				saveTrie(root, filename);
				filenames.push_back(filename);
				data[filename] = root;

				numberOfFile += 1;
				if (numberOfFile % scale == 0 && numberOfFile / scale <= 100) {
					gotoXY(10 + numberOfFile / scale, 0);
					cout << (char)254;
				}
			}
		}
		closedir(dir);
	}
}
void SearchEngine::loadData() { // Load files, stopwords
	DIR* dir; struct dirent* ent;
	int numberOfFile = 0, totalFile = 0, scale, totalLoad = 1000;
	set<string> loaded;

	cout << "Loading - [" << string(100, '=') << ']';

	if ((dir = opendir("Loaded")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] == '.') continue;
			string filename = ent->d_name;
			filename = filename.substr(0, filename.size() - 4);
			loaded.insert(filename);
		}
	}
	
	if ((dir = opendir("DataSearch")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_name[0] == '.') continue;
			totalFile += 1;
		}
	}
	scale = totalFile / 100;
	
	if ((dir = opendir("DataSearch")) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string filename = ent->d_name;
			if (filename[0] == '.') continue;

			if (!loaded.count(filename)) {
				TrieNode* root = new TrieNode();
				loadFile(root, filename);
				saveTrie(root, filename);
				if (totalFile - numberOfFile <= totalLoad + 500) {
					filenames.push_back(filename);
					data[filename] = root;
				} else root->clear();
			}
			else if (totalFile - numberOfFile <= totalLoad) {
				filenames.push_back(filename);
				data[filename] = loadTrie(filename);
			}

			numberOfFile += 1;
			if (numberOfFile % scale == 0 && numberOfFile / scale <= 100) {
				gotoXY(10 + numberOfFile / scale, 0);
				cout << (char)254;
			}
		}
		closedir(dir);
	}

	loadStopword();
	loadSyno();
}
void SearchEngine::loadFile(TrieNode*& root, string filename) {
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
void SearchEngine::loadStopword() {
	ifstream fin;
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
void SearchEngine::loadSyno() {
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
}
void SearchEngine::saveTrie(TrieNode*& root, string filename) {
	string path = "Loaded/" + filename + ".bin";
	ofstream fout(path, ios::binary);

	queue<TrieNode*> Queue;
	Queue.push(root);
	while (!Queue.empty()) {
		TrieNode* node = Queue.front(); Queue.pop();
		for (int i = 0; i < 42; ++i) {
			bool e = node->child[i];
			fout.write((char*)&e, sizeof(bool));
			if (e) Queue.push(node->child[i]);
		}
		fout.write((char*)&node->isWord, sizeof(bool));
		fout.write((char*)&node->isTitle, sizeof(bool));
		int n = node->occurs.size();
		fout.write((char*)&n, sizeof(int));
		for (int i = 0; i < n; ++i)
			fout.write((char*)&node->occurs[i], sizeof(int));
	}

	fout.close();
}
TrieNode* SearchEngine::loadTrie(string filename) {
	string path = "Loaded/" + filename + ".bin";
	ifstream fin(path, ios::binary);

	TrieNode* root = new TrieNode();
	queue<TrieNode*> Queue;
	Queue.push(root);
	while (!Queue.empty()) {
		TrieNode* node = Queue.front(); Queue.pop();
		for (int i = 0; i < 42; ++i) {
			bool e = false;
			fin.read((char*)&e, sizeof(bool));
			if (e) {
				node->child[i] = new TrieNode();
				Queue.push(node->child[i]);
			}
		}
		fin.read((char*)&node->isWord, sizeof(bool));
		fin.read((char*)&node->isTitle, sizeof(bool));
		int n = 0;
		fin.read((char*)&n, sizeof(int));
		node->occurs.resize(n);
		for (int i = 0; i < n; ++i)
			fin.read((char*)&node->occurs[i], sizeof(int));
	}

	fin.close();
	return root;
}
