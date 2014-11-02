//scanner.cpp
//Katharine Thomas & James Wilson
//
/*The scanner function (with help from the overloaded >> operator) scans each token of
an input file and assigns it a "kind" (a terminal value) so it can be properly interpreted
by the parser.
*/

#include "stdafx.h"
#include "scanner.h"
#include "token.h"
#include "derivedToken.h"
#include "utility.h"
#include "symbolTable.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <exception>

using namespace std;


tokenPtr scanner::nextTkn(nullptr);
tokenPtr scanner::currentTkn(nullptr);

set<token> tokenSet;
symbolTable table;


scanner::scanner(ifstream &ifs) : file(ifs) {}

scanner& operator>>(scanner& scan, tokenPtr & t) {
	string str;
	if (scanner::nextTkn != nullptr) t = move(scanner::nextTkn);


	// Should this be an if/else or a try/catch?
	if (scan.file >> str){
		TERMINAL term = str2terminal(str);
		table.update(term, str);
		scanner::nextTkn = table.getToken(term, str);
	} 
	else{ throw string("scanner::EOF");}
	return scan;

}

//---------- Old Version
//scanner& operator>>(scanner& scan, tokenPtr & t) {
//	string str;
//	if (scanner::nextTkn != nullptr) t = move(scanner::nextTkn);
//
//	
//	if (scan.file >> str){
//		
//			//scanner::nextTkn = make_shared<token>(tempStr);
//
//			if (scanner::nextTkn->isLabel()) {
//				table.update(LABEL,tempStr);
//				//shared_ptr<token> tempPtr = table.getToken(LABEL, tempStr);
//				//scanner::nextTkn = move(tempPtr);
//				scanner::nextTkn = table.getToken(LABEL, tempStr);
//			}
//
//			else if (scanner::nextTkn->isNumeric()) {
//				table.update(NUMBER, tempStr);
//				//shared_ptr<token> tempPtr = table.getToken(NUMBER, tempStr);
//				scanner::nextTkn = table.getToken(NUMBER, tempStr);
//			}
//
//			else if (scanner::nextTkn->isLeftParen()) {
//				scanner::nextTkn->kind = LEFTPAREN;
//			}
//
//			else if (scanner::nextTkn->isRightParen()) {
//				scanner::nextTkn->kind = RIGHTPAREN;
//			}
//
//	/*		else if (scanner::nextTkn->isComma()) {
//				scanner::nextTkn->kind = COMMA;
//			}
//
//			else if (scanner::nextTkn->isAnd()) {
//				scanner::nextTkn->kind = AND;
//			}
//
//			else if (scanner::nextTkn->isSep()) {
//				scanner::nextTkn->kind = SEPARATOR;
//			}*/
//	}
//
//	else{
//		throw string("scanner::EOF");
//	}
//	
//	return scan;
//
//}