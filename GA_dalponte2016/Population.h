/*
 * Population.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include<Const.h>
#include<Options.h>
#include<Individual.h>

#include <string>
#include <vector>
#include <thread>

class Population {
public:
	Population(Options options);
	virtual ~Population();
	//------------------------

	Options options;
	Individual *members[MAXPOP];
	double avgFitness, minFitness, maxFitness, sumFitness;

	void Init();
	void Evaluate();
	void Generation(Population *child);
	void Report(unsigned long int gen);
	void Statistics();

	int ProportionalSelector();
	void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	void SBX(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	
	void XoverOnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	void XoverTwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	void XoverUniform(Individual *p1, Individual *p2, Individual *c1, Individual *c2);

	void halve(Population *child);
	void CHCGeneration(Population *child);

	std::string ToString();
};

#endif /* POPULATION_H_ */
