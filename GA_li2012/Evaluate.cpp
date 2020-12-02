/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "Options.h"
#include "Evaluate.h"
#include "Individual.h"
//#include "Graph.h"

#include <math.h>

#include <fstream>
#include <iostream>


double Eval(Individual *individual){
	double sum = 0;
	for(int i = 0; i < individual->chromLength; i++){
		sum += (individual->chromosome[i] == 1 ? 1: 0);
	}
	return sum;
}


/*
void EvalInit(Options options) {
	Graph *g = new Graph(0);
	g->ReadGraph(options.graphInfile);
	std::cout << g->ToString(",");
	std::cout << "ended graph reading and writing" << std::endl;
	g->MakeAdjacencyList();
}
*/
