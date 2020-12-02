/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Options.h>
#include <Evaluate.h>
#include <Individual.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

double Eval(Individual *individual){
	double sum = 0;
	double sumPA = 0; double modelSum = 0;
	string command = "Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/GA_dalponte2016/treeSeg_dalponte.R ";
	
	cout << "Chromosome: ";
	for(int i = 0; i < individual->chromLength; i++){
		cout << individual->chromosome[i] << " ";
		command.append(to_string(individual->chromosome[i]));
		command.append(" ");
		sum += (individual->chromosome[i] == 1 ? 1: 0);
	}
	cout << endl << endl;
	cout << command << endl;
	const char * com = command.c_str();
	system(com);
	cout << endl << endl;
	return sum;
}
