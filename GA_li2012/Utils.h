/*
 * Utils.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <random>
extern std::mt19937 MyRandom;

void InitializeRandomNumberGenerator(int seed);

void WriteBufToFile(std::string buf, std::string filename);

float RandomFraction();
int Flip(float prob);
int IntInRange(int low, int high);
double DoubleInRange(double low, double high);



#endif /* UTILS_H_ */
