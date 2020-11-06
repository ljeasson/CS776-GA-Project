/*
 * Individual.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Individual.h>
#include <Utils.h>

Individual::Individual(int len) {
	// TODO Auto-generated constructor stub
	chromLength = len;
	fitness = -1;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

void Individual::Init(){
	//for(int i = 0; i < chromLength; i++){
	//	chromosome[i] = Flip(0.5f);
	//}
	chromosome[0] = IntInRange(0,4);
	for(int i = 1; i < chromLength; i++){
		chromosome[i] = DoubleInRange(0.01, 20.0);
	}
}

void Individual::Mutate(double pm){
	//for(int i = 0; i < chromLength; i++){
	//	if(Flip(pm))
	//		chromosome[i] = 1 - chromosome[i];
	//}
	if (Flip(pm))
		chromosome[0] = IntInRange(0,4);
	for(int i = 1; i < chromLength; i++){
		if(Flip(pm))
			chromosome[i] = DoubleInRange(0.01, 20.0);
	}
}
