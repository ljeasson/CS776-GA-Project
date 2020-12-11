// CHCGeneticAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <Utils.h>
#include <GA.h>

using namespace std;
int main(int argc, char * argv[])
{
	int low = 1;
	int high = 1000;

	srand(time(NULL));
	int randomSeed = IntInRange(low, high);

	cout << "CHC genetic algorithm: " << argv[0] << endl;
	cout << "Algorithm: silva2016()" << endl;
	cout << "Chromosome: [max_cr_factor, exclusion]" << endl; 

	int runs = 5; //30;
	GA ga(argc, argv, randomSeed);

	for (int i = 0; i < runs; i++)
	{
		ga.Init();
		ga.CHCRun();
	}
	return 0;
}