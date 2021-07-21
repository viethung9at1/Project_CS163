//#include "../models/SearchEngine.h"
//#include<fstream>
//#include<filesystem>
//using namespace std;
//void SearchEngine::loadData() { // Load files, stopwords
//	ifstream fin;
//	using (fs=filesystem)
//}
//void SearchEngine::loadFile(TrieNode*& root, string filename) {
//	
//}

#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::exprt;

int main() {
    std::string path = "/path/to/directory";
    for (const auto& entry : fs::directory_iterator(path))
        std::cout << entry.path() << std::endl;
}