#include<iostream>
#include "models/SearchEngine.h"

using namespace std;

int main()
{
	SearchEngine Google;
	Google.loadData();
	Google.run();

	//system("pause");
}