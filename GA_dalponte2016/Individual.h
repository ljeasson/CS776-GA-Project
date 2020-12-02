/*
 * Individual.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <Const.h>

#include <string>

class Individual {
public:
	Individual(int chromLen);
	virtual ~Individual();

	int chromLength;
	double chromosome[MAX_CHROMLENGTH];
	double fitness;

	void Init();
	void Mutate(float pm);

	std::string ToString();
};

#endif /* INDIVIDUAL_H_ */
