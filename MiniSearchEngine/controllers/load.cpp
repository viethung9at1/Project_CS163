#include "../models/SearchEngine.h"
#include<fstream>
#include<dirent.h>
using std::string;
void SearchEngine::loadData() { // Load files, stopwords
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir("DataSearch")) != NULL) {
		while ((ent = readdir(dir)) != NULL) 
			filenames.push_back(ent->d_name);
		closedir(dir);
	}

}
void SearchEngine::loadFile(TrieNode*& root, string filename) {

}
