// Lab2.cpp
// Katharine Thomas and James Wilson
// Defines the entry point of the program.  It properly parses the input file (parse) and properly 
// prints it to the output file (semAnalysis).

//#include "stdafx.h"
#include "scanner.h"
#include "parse.h"
#include "token.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;



int main(int argc, char* argv[])
{
	string in_file;
	string out_file;
	int result = NO_ERROR;

	if (argc == 3) {
		
		in_file = argv[1];
		out_file = argv[2];
	}
	else {
		cout << "usage: " << argv[0] << " <input_file_name> <output_file_name>" << endl;
		return BAD_INPUT;
	}


	if (parse(in_file) == NO_ERROR) {
		result = semAnalysis(out_file);
		}
	else {
		result = BAD_PARSE;
	}

	return result;
}

