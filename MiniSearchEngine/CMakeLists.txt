# CMakeList.txt : CMake project for MiniSearchEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("MiniSearchEngine")

# Add source to this project's executable.
add_executable (MiniSearchEngine "main.cpp"    "models/SearchEngine.h" "models/Trie.h" "models/console.h" "controllers/console.cpp" "controllers/engine.cpp" "controllers/load.cpp" "controllers/trie.cpp" "controllers/interface.cpp")
# TODO: Add tests and install targets if needed.
