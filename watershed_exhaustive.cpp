// CHCGeneticAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

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

void WriteBufToFile(std::string buf, std::string filename){
	std::ofstream ofs(filename, std::ofstream::app);
	if(ofs.good()){
		ofs << buf;
	}
	ofs.flush();
	ofs.close();
}

double Eval(int th_tree, int tol, int ext){
	
	double fitness = 0;
	int sum = 0;
	
	// Append chromosome genes as Rscript command line arguments
	string command = "Rscript.exe C:/Users/Lee/Desktop/CS776-GA-Project/GA_watershed/treeSeg_watershed.R ";
	command.append(to_string(abs(th_tree)));
	command.append(" ");
	command.append(to_string(abs(tol)));
	command.append(" ");
	command.append(to_string(abs(ext)));
	command.append(" ");
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
	sprintf(printbuf, "%d\t%d\t%d \n%f\n\n", abs(th_tree), abs(tol), abs(ext), fitness);
	WriteBufToFile(string(printbuf), string("C:/Users/Lee/Desktop/CS776-GA-Project/watershed_parameters.txt"));
	cout << printbuf << endl;	

	return fitness;
}

int main(int argc, char * argv[])
{
	cout << "Exhaustive Search: " << argv[0] << endl;
	cout << "Algorithm: watershed()" << endl;
	cout << "Chromosome: [th_tree, tol, ext]" << endl << endl; 

	
	for (int i = 1; i < 20; i++){
		for (int j = 1; j < 50; j++){
			for (int k = 1; j < 100; k++){
				Eval(i,j,k);
			}
		}
	}
	return 0;
}

