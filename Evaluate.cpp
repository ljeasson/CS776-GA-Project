/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Evaluate.h>
#include <math.h>
#include <string>
#include <iostream>

using namespace std;

double Eval(Individual *individual){
	double sum = 0;
	string command = "Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/treeSeg.R ";
	
	cout << "Chromosome: ";
	for(int i = 0; i < individual->chromLength; i++){
		cout << individual->chromosome[i] << " ";
		command.append(to_string(individual->chromosome[i]));
		command.append(" ");
		sum += (individual->chromosome[i] == 1 ? 1: 0);
	}
	cout << endl;
	cout << command << endl;
	const char * com = command.c_str();
	system(com);
	//system("Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/treeSeg.R 3 1.5 2 2 15 2 10");
	cout << endl << endl;
	return sum;
}
