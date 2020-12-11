/*
 * Individual.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Individual.h>
#include <Utils.h>
#include <iostream>

Individual::Individual(int len) {
	// TODO Auto-generated constructor stub
	chromLength = len;
	fitness = -1;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

void Individual::Init(){
	chromosome[0] = DoubleInRange(0.0,0.99); // max_cr_factor
	chromosome[1] = DoubleInRange(0.0,0.95); // exclusion
	
	//std::cout << "Init: " << ToString() << std::endl;
}

void Individual::Mutate(float pm){
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm)){
			switch (i){
				case 0: chromosome[0] = DoubleInRange(0.0,0.99); break; // max_cr_factor
				case 1: chromosome[1] = DoubleInRange(0.0,0.95); break; // exclusion
			}
		}
	}
	//std::cout << "Mutation: " << ToString() << std::endl;
}

std::string Individual::ToString(){
  std::string s = "[ ";
  for(int i = 0; i < chromLength; i++){
    //s = s + (chromosome[i] == 0 ? "0" : "1");
	s = s + std::to_string(chromosome[i]) + " ";
  }
  s = s + "]";

  char str[256];
  sprintf(str, "\nfitness = %f\n", fitness);
  std::string x(str);
  s = s + x;
  return s;
}
    
