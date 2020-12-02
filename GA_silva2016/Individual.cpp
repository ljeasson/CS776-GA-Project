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
	for(int i = 0; i < chromLength; i++){
		chromosome[i] = Flip(0.5f);
	}
}

void Individual::Mutate(float pm){
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm))
			chromosome[i] = 1 - chromosome[i];
	}

}

std::string Individual::ToString(){
  std::string s = "";
  for(int i = 0; i < chromLength; i++){
    s = s + (chromosome[i] == 0 ? "0" : "1");
  }
  char str[256];
  sprintf(str, "\nfitness = %f\n", fitness);
  std::string x(str);
  s = s + x;
  return s;
}
    
