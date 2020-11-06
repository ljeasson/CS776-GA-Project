/*
 * GA.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#ifndef GA_H_
#define GA_H_

#include <Population.h>
#include <Options.h>

class GA {

private:
	void Construct();

public:
	GA(int argc, char *argv[], int randomSeed);

	virtual ~GA();

	//--------------------------------
	Population *parent;
	Population *child;
	Options options;


	void SetupOptions(int argc, char*argv[], int randomSeed);

	void Init();
	void Run();

};

#endif /* GA_H_ */
