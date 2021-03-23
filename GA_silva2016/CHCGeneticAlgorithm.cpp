#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <ctime>

#include <Utils.h>
#include <GA.h>

#include <unistd.h>

using namespace std;

void runGA(int i, int argc, char * argv[], int randomSeed){
	//cout << "RUN on thread " << i << endl;
	GA ga(argc, argv, randomSeed);
	ga.Init();
	ga.CHCRun();
}

int main(int argc, char * argv[])
{
	int low = 1;
	int high = 1000;
	int runs = 5;
	int randomSeed;

	vector<thread> threads;
	srand(time(NULL));

	cout << "Algorithm: silva2016()" << endl;
	cout << "Chromosome: [max_cr_factor, exclusion]" << endl << endl; 	

	for (int i = 0; i < runs; i++)
	{
		randomSeed = IntInRange(low, high);
		threads.push_back(thread(runGA, i, argc, argv, randomSeed));
	}
	for (auto &th : threads) th.join();
	return 0;
}