//scanner.h
//Katharine Thomas & James Wilson
//Prototype for functions of the scanner class

#ifndef SCANNER_H
#define SCANNER_H

#include "stdafx.h"
#include "token.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <deque>



class scanner {
private:
	ifstream& file;
	string expt;


public:
	static tokenPtr nextTkn, currentTkn;
	scanner(ifstream& ifs);

	operator bool() {
		if (file) {
			return true;
		}
		return false;
	}

	friend scanner& operator>>(scanner& scan, tokenPtr & t);

};


#endif