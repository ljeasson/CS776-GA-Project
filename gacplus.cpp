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
	int randomSeed1 = 1; int randomSeed2 = 1; int randomSeed3 = 1; int randomSeed4 = 1;
	srand(time(NULL));

	randomSeed1 = IntInRange(low, high); //rand() % ( high - low + 1 ) + low;
	randomSeed2 = IntInRange(low, high); //rand() % ( high - low + 1 ) + low;
	randomSeed3 = IntInRange(low, high); //rand() % ( high - low + 1 ) + low;
	randomSeed4 = IntInRange(low, high); //rand() % ( high - low + 1 ) + low;
	
	// dalponte2016()
	GA ga1 = GA(argc, argv, randomSeed1);
	ga1.Init();
	
	// watershed()
	GA ga2 = GA(argc, argv, randomSeed2);
	ga2.Init();

	// li2012()
	GA ga3 = GA(argc, argv, randomSeed3);
	ga3.Init();
	
	// silva2016()
	GA ga4 = GA(argc, argv, randomSeed4);
	ga4.Init();

	
	ga1.CHCRun();
	ga2.CHCRun();
	ga3.CHCRun();
	ga4.CHCRun();

	return 0;
}
