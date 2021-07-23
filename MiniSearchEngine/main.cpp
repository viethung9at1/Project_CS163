#include<iostream>
#include "models/SearchEngine.h"
#include<fstream>

using namespace std;

int main()
{
	SearchEngine Google;
	Google.loadData();
	Google.run();
}