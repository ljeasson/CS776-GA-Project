//============================================================================
// Name        : gacplus.cpp
// Author      : Sushil J Louis
// Version     :
// Copyright   : Copyright University of Nevada, Reno
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <GA.h>
using namespace std;

int main(int argc, char *argv[]) {
	cout << "Tree Segmentation GA" << endl;
	int maxRuns = 30;

	for (int i = 1; i <= maxRuns; i++) {
		cout << "Run " << i << endl;

		GA ga = GA(argc, argv);

		ga.Init();
		ga.Run();
		cout << endl;
	}

	return 0;
}
