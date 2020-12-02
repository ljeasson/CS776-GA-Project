/*
 * Utils.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "Utils.h"
#include<iostream>
#include<fstream>
#include<string>
#include <random>

std::mt19937 MyRandom;
std::uniform_real_distribution<float> uniformFloat01Distribution;

void WriteBufToFile(std::string buf, std::string filename){
	std::ofstream ofs(filename, std::ofstream::app);
	if(ofs.good()){
		ofs << buf;
	}
	ofs.flush();
	ofs.close();
}

void InitializeRandomNumberGenerator(int seed) {
	MyRandom = std::mt19937(seed);
	uniformFloat01Distribution = std::uniform_real_distribution<float> (0.0f, 1.0f);
}


int Flip(float prob){
	int f = (MyRandom() < prob * MyRandom.max() ? 1 : 0);
	return f;
}

/* greater than equal to low and strictly less than high */
int IntInRange(int low, int high){
	return low + MyRandom()%(high - low);
}

/* greater than equal to 0 and less than 1 */
float RandomFraction(){
	return ((float)(MyRandom() % 1000)) / (float)1000.0;
	//return uniformFloat01Distribution(random);
}

