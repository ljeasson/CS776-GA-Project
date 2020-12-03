/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Options.h>
#include <Evaluate.h>
#include <Individual.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
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

double Eval(Individual *individual){
	double fitness = 0;
	double objective = 0;

	// Append chromosome genes as Rscript command line arguments
	string command = "Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/GA_dalponte2016/treeSeg_dalponte2016.R ";
	cout << "Chromosome: ";
	for(int i = 0; i < individual->chromLength; i++){
		cout << individual->chromosome[i] << " ";
		command.append(to_string(individual->chromosome[i]));
		command.append(" ");
	}
	cout << endl << endl << command << endl << endl;

	// Call Rscript to run tree segmentation with parameters
	// Get console output as string
	const char * com = command.c_str();
	string console_output = exec(com);	
	string RESULT = console_output.substr(console_output.find("RESULT:")+9, console_output.back());
	cout << endl;

	// Split final result vector into float values
	// Get fitness
	vector<double> tree_seg_results = split(RESULT, " ");
	for (auto & element : tree_seg_results) {
    	cout << element << endl;
		fitness += element;
	}
	cout << "FITNESS: " << fitness << endl;
	
	// Calculate objective function based on fitness
	// MINIMIZE: Presence/absence detection proportion
	// OPTION A: g(x) = 1/f(x1) + 1/f(x2) + ... + 1/f(xN)
	/*
	for (auto & element : tree_seg_results) {
    	objective += (1/element);
	}
	*/
	// OPTION B: g(x) = 1/ (f(x1) + f(x2) + ... + f(xN))
	objective = 1/fitness;
	
	cout << "OBJECTIVE FUNCTION: " << objective << endl << endl;
	return objective;
}