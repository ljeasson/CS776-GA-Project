/*
 * GA.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "GA.h"
#include "Utils.h"
#include "Evaluate.h"

#include <string>
#include<iostream>

GA::GA(int argc, char *argv[]) {
	SetupOptions(argc, argv);
	InitializeRandomNumberGenerator(options.randomSeed);
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}


void GA::SetupOptions(int argc, char *argv[]){
	options.randomSeed = 121;
	options.popSize = 20;
	options.chromLength = 100;
	options.maxgens = 20;
	options.px = 0.95f;
	options.pm = 0.01f;
	options.infile = std::string ("infile");
	options.outfile = std::string("outfile");
	//options.graphInfile = std::string("graph-raw.csv");
}

void GA::Init(){
	//EvalInit(options);
	parent = new Population(options);
	child  = new Population(options);
	parent->Init(); // evaluates, stats, and reports on initial population
	parent->Statistics();
	parent->Report(0);

}

void GA::Run(){
	for (unsigned long int i = 1; i < options.maxgens; i++) {
		parent->Generation(child);
		child->Evaluate();
		child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;
	}

}

void GA::CHCRun() {
	for (unsigned long int i = 1; i < options.maxgens; i++) {
		parent->CHCGeneration(child);
		child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;
	}
}

