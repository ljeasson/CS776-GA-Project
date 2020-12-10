/*
 * Population.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "Population.h"
#include <assert.h>
#include <Evaluate.h>
#include <Utils.h>
#include <iostream>

#include <cstring>

Population::Population(Options opts) {
	options = opts;
	avgFitness = minFitness = maxFitness = sumFitness = -1;
	assert(options.popSize * 2 <= MAXPOP);
	for (int i = 0; i < options.popSize * 2; i++){
		members[i] = new Individual(options.chromLength);
		members[i]->Init();
	}
}

Population::~Population() {
	// TODO Auto-generated destructor stub
}

void Population::Init(){
	Evaluate();
}

void Population::Evaluate(){
	for (int i = 0; i < options.popSize; i++){
		members[i]->fitness = Eval(members[i]);
	}
}

void Population::Statistics(){
	sumFitness = 0;
	minFitness = members[0]->fitness;
	maxFitness = members[0]->fitness;
	
	for(int i = 0; i < options.popSize; i++){
		sumFitness += members[i]->fitness;

		if(minFitness > members[i]->fitness)
			minFitness = members[i]->fitness;
		if(maxFitness < members[i]->fitness)
			maxFitness = members[i]->fitness;
	}
	avgFitness = sumFitness/options.popSize;
}

void Population::Report(unsigned long int gen){
	char printbuf[1024];
	sprintf(printbuf, "%4i \t %f \t %f \t %f\n", (int)gen, minFitness, avgFitness, maxFitness);
	WriteBufToFile(std::string(printbuf), options.outfile);
	std::cout << printbuf;
}

void Population::Generation(Population *child){
	int pi1, pi2, ci1, ci2;
	Individual *p1, *p2, *c1, *c2;
	for (int i = 0; i < options.popSize; i += 2) {
		pi1 = ProportionalSelector();
		pi2 = ProportionalSelector();

		ci1 = i;
		ci2 = i + 1;

		p1 = members[pi1]; p2 = members[pi2];
		c1 = child->members[ci1]; c2 = child->members[ci2];

		XoverAndMutate(p1, p2, c1, c2);
	}
}

void Population::CHCGeneration(Population *child) {
	int pi1, pi2, ci1, ci2;
	Individual *p1, *p2, *c1, *c2;
	
	//std::cout << "Parents" << std::endl;
	//std::cout << ToString(0, options.popSize);
	
	for (int i = 0; i < options.popSize; i += 2) {
		pi1 = ProportionalSelector();
		pi2 = ProportionalSelector();

		ci1 = options.popSize + i;
		ci2 = options.popSize + i + 1;

		p1 = members[pi1]; p2 = members[pi2];
		c1 = members[ci1]; c2 = members[ci2];

		XoverAndMutate(p1, p2, c1, c2);
	}
	halve(child);
}

int compareFitness(const void *x, const void *y) {
  Individual **a = (Individual **) x;
  Individual **b = (Individual **) y;
  //std::cout << "before comparison\n";
  //std::cout << "comparing " << (*a)->ToString() << " against " << (*b)->ToString() << std::endl;
  return (int) ( (*a)->fitness - (*b)->fitness);
}

void Population::halve(Population*child) {
  for (int i = options.popSize; i < 2 * options.popSize; i++){
    members[i]->fitness = Eval(members[i]);
  }
  //std::cout << "Intermediate\n";
  //std::cout << ToString(options.popSize, options.popSize * 2);
  qsort(members, options.popSize * 2, sizeof(Individual *), compareFitness);
  //std::cout << "Sorted Parents + children\n";
  //std::cout << ToString(0, options.popSize * 2);
  for(int i = 0; i < options.popSize; i++){
	  memcpy(child->members[i], members[options.popSize + i], sizeof(Individual));
  }
  //std::cout << "Children\n";
  //std::cout << child->ToString(0, options.popSize);  
}

std::string Population::ToString(int start, int end){
  std::string s = "";
  for(int i = start; i < end; i++){
    s = s + members[i]->ToString();
    s = s + "------------\n";
  }
  return s;
}

int Population::ProportionalSelector(){
	int i = -1;
	double sum = 0;
	double limit = RandomFraction() * sumFitness;
	do {
		i = i + 1;
		sum += members[i]->fitness;
	} while (sum < limit && i < options.popSize-1 );
	//std::cout << i << " \n";
	return i;
}


void Population::XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2){

	for(int i = 0; i < options.chromLength; i++){ //First copy
		c1->chromosome[i] = p1->chromosome[i];
		c2->chromosome[i] = p2->chromosome[i];
	}
	if(Flip(options.px)){ // if prob, then cross/exchange bits
		SBX(p1, p2, c1, c2);
	}

	c1->Mutate(options.pm);
	c2->Mutate(options.pm);
}

void Population::SBX(Individual *p1, Individual *p2, Individual *c1, Individual *c2){
    
    // Calculate Beta
    double u = DoubleInRange(0,1);
    double beta;
    double nc = 20; // nc = 2 (closer to parents), nc = 5 (far from parents)
    if (u <= 0.5)
        beta = pow( 2*u, 1/(nc+1) );
    else
        beta = pow ( 1/(2*(1-u)), 1/(nc+1) );

    // Create children based on Beta 
    for(int i = 0; i < options.chromLength; i++){
        c1->chromosome[i] = 0.5 * ( (1+beta)*p1->chromosome[i] + (1-beta)*p2->chromosome[i] );
        c2->chromosome[i] = 0.5 * ( (1-beta)*p1->chromosome[i] + (1+beta)*p2->chromosome[i] );
    }
}



void Population::XoverOnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){	
	// Exchange algorithm and parameter bits
	int t1 = IntInRange(0, options.chromLength);
	for(int i = t1; i < options.chromLength; i++){
		c1->chromosome[i] = p2->chromosome[i];
		c2->chromosome[i] = p1->chromosome[i];
	}
}

void Population::XoverTwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){
	// Exchange algorithm bit
	c1->chromosome[0] = p2->chromosome[0];
	c2->chromosome[0] = p1->chromosome[0];

	// Exchange parameter bits
	int t1 = IntInRange(0, options.chromLength);
	for(int i = t1; i < options.chromLength; i++){
		c1->chromosome[i] = p2->chromosome[i];
		c2->chromosome[i] = p1->chromosome[i];
	}
}

void Population::XoverUniform(Individual *p1, Individual *p2, Individual *c1, Individual *c2){
	// Exchange all bits with equal probability
	for(int i = 0; i < options.chromLength; i++){
		if (Flip(0.5))
			c1->chromosome[i] = p2->chromosome[i];
		else
			c1->chromosome[i] = p1->chromosome[i];

		if (Flip(0.5))
			c2->chromosome[i] = p1->chromosome[i];
		else
			c2->chromosome[i] = p2->chromosome[i];
		
	}
}
