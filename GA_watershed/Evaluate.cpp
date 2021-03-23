/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Evaluate.h>
#include <Utils.h>
#include <math.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <stdexcept>

#include <string>
#include <vector>

using namespace std;

string exec(const char* cmd) {
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

vector<double> split(const string& str, const string& delim)
{
    vector<string> tokens;
	vector<double> token_nums;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());

	for (auto & element : tokens) {
    	double temp = ::atof(element.c_str());
		token_nums.push_back(temp);
	}

    return token_nums;
}

double Eval(Individual *individual, Options options){
	
	double fitness = 0;
	int sum = 0;
	
	// Append chromosome genes as Rscript command line arguments
	string command = "Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/treeSeg_watershed_hillclimb.R ";
	cout << "Chromosome: ";
	for(int i = 0; i < individual->chromLength; i++){
		cout << individual->chromosome[i] << " ";
		command.append(to_string(abs((int)individual->chromosome[i])));
		command.append(" ");

		//fitness += individual->chromosome[i];
	}
	cout << endl << command << endl << endl;


	// Call Rscript to run tree segmentation with parameters
	// Get console output as string
	const char * com = command.c_str();
	string console_output = exec(com);	
	string RESULT = console_output.substr(console_output.find("RESULT:")+9, console_output.back());
	cout << endl;

	// Split final result vector into float values
	// Calculate fitness: f(x) = (f(x1) + f(x2) + ... + f(xN)) / N
	// MAXIMIZE: Overlap detection proportion
	vector<double> tree_seg_results = split(RESULT, " ");
	for (auto & element : tree_seg_results) {
		fitness += element;
		sum++;
	}
	fitness /= sum;
	

	char printbuf[1024];
	sprintf(printbuf, "%d\t%d\t%d \n%f\n\n", abs((int)individual->chromosome[0]), abs((int)individual->chromosome[1]), abs((int)individual->chromosome[2]), fitness);
	WriteBufToFile(string(printbuf), options.parametersfile);
	//WriteBufToFile(string(printbuf), string("C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/parameters.txt"));
	cout << printbuf << endl;	

	return fitness;
}