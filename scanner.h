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
	//static tokenPtr currentTkn;
	
	//shared_ptr<token> nextTokenPtr;
	//string phrase;
	//string horn;
	string expt;
	/*vector<shared_ptr<token>> phrase;
	vector<token> horn;*/

public:
	static tokenPtr nextTkn, currentTkn;
	scanner(ifstream& ifs);

	operator bool() {
		if (file) {
			return true;
		}
		return false;
	}

	friend scanner& operator>>(scanner& scan, dequeTP & v);
	friend scanner& operator>>(scanner& scan, token & t);
	friend scanner& operator>>(scanner& scan, tokenPtr & t);
	//

	//friend scanner& operator>>(scanner& scan, vector<token> & d);
	//friend scanner& operator>>(scanner& scan, vector<tokenPtr> & d);

	//friend scanner& operator>>(scanner& scan, deque<token> & v);
	

};


#endif