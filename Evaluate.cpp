/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Evaluate.h>
#include <math.h>
#include <string>

using namespace std;

double Eval(Individual *individual){
	double sum = 0;
	for(int i = 0; i < individual->chromLength; i++){
		sum += (individual->chromosome[i] == 1 ? 1: 0);
	}
	
	//const char* r_execute = "C:/Program Files/R/R-4.0.3/bin/x64/Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/treeSeg.R 3 1.5 2 2 15 2 10";
	//const char* r_execute = "Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/treeSeg.R 3 1.5 2 2 15 2 10";
	//FILE *fp = popen(r_execute ,"r");
	system("Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/treeSeg.R 3 1.5 2 2 15 2 10");
	return sum;
}
