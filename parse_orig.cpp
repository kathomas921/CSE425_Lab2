//parse.cpp
//Katharine Thomas & James Wilson
//
/*The parse function (with accompanying helper functions) inspect an input file
token by token to determine whether it can find a propery formed hornStr Clause given
the context-free grammar shown in ReadMe.txt.
*/

#include "stdafx.h"
#include "parse.h"
#include "scanner.h"
#include "phrase.h"
#include "token.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>




using namespace std;


//token currentTkn, nextTkn;
scanner* scan;
string phrase;

dequeTP phraseDev;

string hornStr;
string expt;

TERMINAL exptDev;

dequeTP hornDev;

//phrasePtr currentPhrase;

hornPtr currentHorn;
headPtr currentHead;
bodyPtr currentBody;
predPtr currentPred;
namePtr currentName;
symbPtr currentSymb;



bool isKind(TERMINAL kind, tokenPtr thisToken){
	return kind == thisToken->kind;
}

bool isKind(string kind, tokenPtr thisToken){
	return kind.compare(terminal_to_string(thisToken->kind));
}

void advance(){

	//How do we adjust this?
	if (phrase.length() == 0) {
		phrase += scan->nextTkn->str;
	}
	else {
		phrase += (" " + scan->nextTkn->str);
	}

	//currentTkn = nextTkn;
	//if (!(*scan >> nextTkn)) {
	//	token a;
	//	nextTkn = a;
	//}
	//end case
	//currentTkn = nextTkn; //is this correct shallow vs deep?
	if (!(*scan >> phraseDev)) {
		scan->nextTkn->kind = UNKNOWN;
	}

}

void expect(TERMINAL t){
	expt = terminal_to_string(t);
	//exptDev = make_shared<token>()
	if (scan->nextTkn->kind == t) {
		advance();
	}
	else
		throw "Expected token not found.";
}



void isSymbol() {
	if (scan->nextTkn->kind != LABEL && scan->nextTkn->kind != NUMBER) {
		expt = "SYMBOL";
		throw "Incorrectly formed Symbol clause";
	}
	else {
		//currentSymb = move(scan->nextTkn)
		currentSymb = make_shared<symb>(scan->nextTkn);
		advance();
	}
}


void isArgs(){
	bool status = true;
	bool delimiter = false;
	int count = 0;
	while (scan->nextTkn->kind != RIGHTPAREN){
		if (delimiter){
			expect(COMMA);
			delimiter = false;
			count += 1;
		}
		if (!delimiter){
			isSymbol();
			currentPred->s.push_back(move(currentSymb));
			count += 1;
			delimiter = true;
		}
		if (count % 2 == 0){
			expt = "SYMBOL";
			throw "Incorrectly formed Args clause";
		}
	}
}

void isPredicate(){

	if (!scan->currentTkn->isLabel()){
		expt = "START_LABEL";
		throw "Incorrectly formed Predicate clause: Doesn't start with Label";
	}

	try{

		expect(LEFTPAREN);
		if (!scan->nextTkn->isRightParen()){
			expt = "LABEL";
			isArgs();
		}
		expect(RIGHTPAREN);
	}

	catch (...){
		throw "Incorrectly formed Predicate clause";
	}

}

void isBody(){
	bool status = true;
	bool delimiter = false;
	int count = 0;
	while (status){
		if (delimiter){
			if (scan->nextTkn->kind == AND) {
				expect(AND);
				delimiter = false;
				count += 1;
			}
			else {
				status = false;
			}
		}

		if (!delimiter) {
			if (scan->currentTkn->isAnd()) {
				advance();
			}
			isPredicate();
			currentBody->p.push_back(move(currentPred));

			count += 1;
			delimiter = true;
		}

		if (count % 2 == 0)
			throw "Incorrectly formed Body clause";
	}
}

void isHead(){
	try{
		isPredicate();
		currentHead->p = move(currentPred);
	}
	catch (const char* e) {
		string rcvd = terminal_to_string(scan->nextTkn->kind);
		cout << endl << "Error detected: " << e << endl;
	}

}

void isHorn(){

	try{
		isHead();
		currentHorn->h = move(currentHead);
		hornDev = phraseDev;

		if (scan->nextTkn->isSep()){
			advance();
			advance();
			isBody();
			currentHorn->b = move(currentBody);
			hornDev = phraseDev;
		}
	}
	catch (const char* e) {
		string rcvd = terminal_to_string(scan->nextTkn->kind);
		cout << endl << "Error detected: " << e << endl;

		if (expt == "COMMA") {
			expt = "COMMA OR RIGHTPAREN";
		}

		if (expt != "START_LABEL") {
			advance();
		}

		if (expt == "START_LABEL") {
			expt = "LABEL";
			rcvd = terminal_to_string(scan->currentTkn->kind);
		}

		cout << "Expected: " << expt << ", Received: " << rcvd << endl;
		cout << "Tokens seen so far in clause: " << phrase << endl;
		phrase.clear();
	}
}



int parse(string &input, string &output) {
	ifstream ifs(input);
	if (!ifs) {
		cout << "Error: could not open file." << endl;
		return BAD_IF;
	}
	ofstream ofs(output);
	if (!ofs) {
		cout << "Error: could not write to output file." << endl;
		return BAD_OF;
	}
	scanner orig(ifs);
	scan = &orig;

	try {
		//*scan >> currentTkn;
		//*scan >> phraseDev;
		*scan >> phraseDev;
		if (!(*scan >> phraseDev)) {
			throw "Parse error";
		}
		//phraseDev.push_back(currentTkn.str);
		//phrase += currentTkn.str;
	}
	catch (const char* e){
		cout << "Parse error detected. Too few inputs to parse tokens." << endl;
		return NO_ERROR;
	}


	while (true){
		try{
			while (ifs) {
				isHorn();
				if (hornStr.length() > 0) {
					ofs << hornStr << endl;
				}
				phraseDev.clear();
				currentHorn.reset();
				hornStr.clear();
				advance();
			}
		}
		catch (...){}

		try {
			advance();
		}
		catch (...) {}

		return NO_ERROR;
	}

}