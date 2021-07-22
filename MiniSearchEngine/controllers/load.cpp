#include "../models/SearchEngine.h"
#include<fstream>
#include<filesystem>
using namespace std;
namespace fs = std::filesystem;
void SearchEngine::loadData() { // Load files, stopwords
	ifstream fin;
	string path = "//DataSearch";
	for (const auto& entry : fs::directory_iterator(path))
		std::cout << entry.path() << std::endl;
}
void SearchEngine::loadFile(TrieNode*& root, string filename) {
	
}
