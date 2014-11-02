////scanner_dev.cpp
////Katharine Thomas & James Wilson
////
///*The scanner function (with help from the overloaded >> operator) scans each token of
//an input file and assigns it a "kind" (a terminal value) so it can be properly interpreted
//by the parser.
//*/
//
#include "stdafx.h"
//#include "scanner.h"
//#include "token.h"
//#include "derivedToken.h"
//#include <iostream>
//#include <fstream>
//#include <algorithm>
//#include <string>
//#include <exception>
//#include <memory>
//
//using namespace std;
//
//scanner::tokenPtr currentTkn(nullptr);
//
//scanner::scanner(ifstream &ifs) : file(ifs) {
//	//curTokenPtr = make_shared<token>(UNKNOWN, "");
//	//nextTokenPtr = make_shared<token>(UNKNOWN, "");
//}
//
//
//scanner& operator>>(scanner& scan, token& t) {
//	string tempStr;
//	if (scan.file >> tempStr) {
//		/*scanner::tokenPtr tempTkn(new token(tempStr));
//		currentTkn = move(tempTkn);*/
//
//		currentTkn = make_shared<token>(new token(tempStr));
//
//		//curTokenPtr = make_shared<token>(&t);
//
//
//		if ((*currentTkn).isLabel()) {
//			currentTkn = make_shared<label>(new label((*currentTkn).str));
//			/*auto lab = make_shared<label>(t.str);
//			scan.phrase.push_back(lab);*/
//			//t.kind = LABEL;
//		}
//
//		else if ((*currentTkn).isNumeric()) {
//			//scan.curTokenPtr = make_shared<number>(t.str);
//			currentTkn = make_shared<number>(new number((*currentTkn).str));
//			//t.kind = NUMBER;
//		}
//
//		else if ((*currentTkn).isLeftParen()) {
//			//scan.curTokenPtr = make_shared<token>(LEFTPAREN, t.str);
//			//t.kind = LEFTPAREN;
//			(*currentTkn).kind = LEFTPAREN;
//		}
//
//		else if ((*currentTkn).isRightParen()) {
//			//scan.curTokenPtr = make_shared<token>(RIGHTPAREN, t.str);
//			//t.kind = RIGHTPAREN;
//
//		}
//
//		else if ((*currentTkn).isComma()) {
//			//scan.curTokenPtr = make_shared<token>(COMMA, t.str);
//			//t.kind = COMMA;
//			(*currentTkn).kind = COMMA;
//		}
//
//		else if ((*currentTkn).isAnd()) {
//			scan.curTokenPtr = make_shared<token>(AND, t.str);
//			//t.kind = AND;
//		}
//
//		else if ((*currentTkn).isSep()) {
//			scan.curTokenPtr = make_shared<token>(SEPARATOR, t.str);
//			//t.kind = SEPARATOR;
//		}
//
//		else {
//			scan.curTokenPtr = make_shared<token>(UNKNOWN, t.str);
//			//t.kind = UNKNOWN;
//		} //stays as UNKNOWN
//
//	}
//
//
//	return scan;
//
//}