//============================================================================
// Name        : gacplus.cpp
// Author      : Sushil J Louis
// Version     :
// Copyright   : Copyright University of Nevada, Reno
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <Utils.h>
#include <GA.h>

using namespace std;

int main(int argc, char *argv[]) {

	int low = 1;
	int high = 1000;
	int randomSeed = 1;
	srand(time(NULL));

	randomSeed = IntInRange(low, high); //rand() % ( high - low + 1 ) + low;
	GA ga = GA(argc, argv, randomSeed);

	ga.Init();
	ga.Run();

	return 0;
}
