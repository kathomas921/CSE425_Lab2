//scanner.cpp
//Katharine Thomas & James Wilson
//
/*The scanner function (with help from the overloaded >> operator) scans each token of
an input file and, creates a smart pointer to that token, and assigns it a "kind" 
(a terminal value) so it can be properly interpreted by the parser.
*/

//#include "stdafx.h"
#include "scanner.h"
#include "token.h"
#include "derivedToken.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <exception>
#include "utility.h"
#include <string>
using namespace std;


tokenPtr scanner::nextTkn(nullptr);
tokenPtr scanner::currentTkn(nullptr);

scanner::scanner(ifstream &ifs) : file(ifs) {}


scanner& operator>>(scanner& scan, tokenPtr & t) {
   // cout << "in scan >> op" << endl;
	string tempStr;
   // cout << "check if next token: " << endl;
    if (scanner::nextTkn != nullptr) {
        t = move(scanner::nextTkn);
        cout << "next token exists: " << scanner::nextTkn->str << endl;
    }
    else{
        cout << "no next token" << endl;
    }

	if (scan.file >> tempStr){
        cout << "tempStr: " << tempStr << endl;
			scanner::nextTkn = make_shared<token>(tempStr);

			if (scanner::nextTkn->isLabel()) {
				shared_ptr<label> tempPtr = shared_ptr<label>(new label(tempStr));
				scanner::nextTkn = move(tempPtr);
			}

			else if (scanner::nextTkn->isNumeric()) {
				scanner::nextTkn = make_shared<number>(tempStr);
			}

			else if (scanner::nextTkn->isLeftParen()) {
				scanner::nextTkn->kind = LEFTPAREN;
			}

			else if (scanner::nextTkn->isRightParen()) {
				scanner::nextTkn->kind = RIGHTPAREN;
			}

			else if (scanner::nextTkn->isComma()) {
				scanner::nextTkn->kind = COMMA;
			}

			else if (scanner::nextTkn->isAnd()) {
				scanner::nextTkn->kind = AND;
			}

			else if (scanner::nextTkn->isSep()) {
				scanner::nextTkn->kind = SEPARATOR;
			}
	}

	else{
      //  cout << "scanner EOF" << endl;
		throw string("scanner::EOF");
	}
	
	return scan;

}