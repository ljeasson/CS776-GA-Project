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
	
	chromosome[0] = IntInRange(1,20); // th_tree
	chromosome[1] = IntInRange(1,50); // tol
	chromosome[2] = IntInRange(1,100); // ext
	
	//std::cout << "Init: " << ToString() << std::endl;
}

void Individual::Mutate(float pm){
	
	//std::cout << "BEFORE Mutation: " << ToString() << std::endl;
	
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm)){
			switch (i){
				case 0: chromosome[0] = IntInRange(1,20); break; // th_tree
				case 1: chromosome[1] = IntInRange(1,50); break; // tol
				case 2: chromosome[2] = IntInRange(1,100); break; // ext
			}
		}
	}
		
	//std::cout << "AFTER Mutation: " << ToString() << std::endl;
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
    
