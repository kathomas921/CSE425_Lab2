//parse.cpp
//Katharine Thomas & James Wilson
//
/*The parse function (with accompanying helper functions) inspect an input file
token by token to determine whether it can find a propery formed hornStr Clause given
the context-free grammar shown in ReadMe.txt. The semAnalysis function prints the horn
clauses as well as unique labels and numbers to the output file.
*/

//#include "stdafx.h"
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
#include "utility.h"
#include <string>



using namespace std;

deque<dequeTP> hornClause;

scanner* scan;

int tokenNum;
string expt;
string rcvd;

TERMINAL exptDev;

dequeTP hornDev;

dequeTP currentPhrase;

symbPtr currentSymb(new symb());
namePtr currentName(new name());
predPtr currentPred(new pred());
predD tempPD; // = new deque<predPtr>;
headPtr currentHead(new head(currentPred));
bodyPtr currentBody(new body(tempPD));
hornPtr currentHorn(new horn(currentHead, currentBody));


bool isKind(TERMINAL kind, tokenPtr thisToken){
	return kind == thisToken->kind;
}

bool isKind(string kind, tokenPtr thisToken){
	return kind.compare(terminal_to_string(thisToken->kind));
}

void advance(){
	++tokenNum;


	try{
        cout << "tokenNum: " << tokenNum << ", advance() try to scan" << endl;
		*scan >> scan->currentTkn;
	}
	catch (string& s){
        cout << "advance:: caught msg: " << s << endl << endl;
		throw ERRORS(END);
	}
//    catch (...){
//        cout << "advance::unexpected error "<< endl;
//        throw string("advance::scanning error");
//    }
	currentPhrase.push_back(scan->nextTkn);

}

void expectNext(TERMINAL t){
	expt = terminal_to_string(t);

	if (scan->nextTkn->kind != t) {
		throw string("Expected token not found.");
	}
	else
		return;
}



void isSymbol() {
	if (scan->nextTkn->kind != LABEL && scan->nextTkn->kind != NUMBER) {
		expt = "SYMBOL";
		throw string("Incorrectly formed Symbol clause");
	}
	else {
		currentSymb = make_shared<symb>(scan->nextTkn);
	}
	currentSymb->complete = true;
}


void isName(){
	
	if (scan->currentTkn->isLabel()){
		currentName = make_shared<name>(scan->currentTkn);
	}
	else{
		expt = "LABEL";
		throw string("Incorrectly formed name");
	}

}

void isArgs(){
	bool status = true;
	bool delimiter = false;
	int count = 0;
	while (scan->nextTkn->kind != RIGHTPAREN){

		if (delimiter){
			expectNext(COMMA);
			advance();
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
			throw string("Incorrectly formed Args clause");
		}
		advance();
	}
}


void isPredicate(){
	if (currentPred == nullptr) currentPred = make_shared<pred>();

	try{
		isName();
		currentPred->n = move(currentName);

		expectNext(LEFTPAREN);
        cout << "isPred 1 calls advance()" << endl;

		advance();

		if (!scan->nextTkn->isRightParen()){
			expt = "LABEL";
			isArgs();

		}
		expectNext(RIGHTPAREN);
		currentPred->complete = true;
        cout << "isPred 2 calls advance() " << endl;

		advance();


	}
	catch (string &s) {
        /////////////
        cout << "isPred: caught msg: " << s << endl;
        ////////////
		if (!currentPred->complete) {
		throw string("Incorrectly formed Predicate clause");
		}
		else
			return;
	}
    /////////////
//    catch (...) {
//        cout << "isPred: unexpected error" << endl;
//        throw string("Incorrectly formed Predicate clause");
//
//    }
    /////////////
}

void isBody(){
	if (currentBody == nullptr) currentBody = make_shared<body>();
	bool status = true;
	bool delimiter = false;
	int count = 0;
	while (status){
		if (delimiter){
			if (scan->nextTkn->kind == AND) {
				expectNext(AND);
                cout << "isBody 1 calling advance()" << endl;

				advance();
				delimiter = false;
				count += 1;
			}
			else {
				status = false;
			}
		}

		if (!delimiter) {
			if (scan->currentTkn->isAnd()) {
                cout << "isBody 2 calling advance()" << endl;

				advance();
			}
			isPredicate();
			currentBody->p.push_back(move(currentPred));
			count += 1;
			delimiter = true;
		}

		if (count % 2 == 0)
			throw string("Incorrectly formed Body clause");
	}
	currentBody->complete = true;
}

void isHead(){
	if (currentHead == nullptr) currentHead = make_shared<head>();

	isPredicate();
	currentHead->p = move(currentPred);
	currentHead->complete = true;
}

void isHorn(){
	if (currentHorn == nullptr) currentHorn = make_shared<horn>();
	try {
		isHead();
		currentHorn->h = move(currentHead);

		if (scan->nextTkn != nullptr && scan->nextTkn->isSep()){
			advance();
			advance();
			isBody();
			currentHorn->b = move(currentBody);
		}
		currentHorn->complete = true;
	}
	catch (string &s) {
		rcvd = terminal_to_string(scan->nextTkn->kind);
		if (expt != rcvd) {
			cout << endl << "Error detected @ ";

			if (expt == "COMMA") {
				expt = "COMMA OR RIGHTPAREN";
			}

			if (expt == "START_LABEL") {
				expt = "LABEL";
				rcvd = terminal_to_string(scan->currentTkn->kind);
			}
		
			cout << "Input token: " << tokenNum << " -> Expected: " << expt << ", Received: " << rcvd << endl;
			cout << "Tokens seen so far in clause: ";
			for (tokenPtr tp : currentPhrase)
			{
				cout << tp << " ";
			}
			cout << endl;
			currentPhrase.clear();

		}
	}
}



int parse(string &input) {

	ifstream ifs(input);
	if (!ifs) {
		return BAD_IF;
	}

	scanner orig(ifs);
	scan = &orig;

	try {
		advance();
		advance();
	}
	catch (string &s){
		cout << "Parse error detected. Too few inputs to parse tokens." << endl;
		return BAD_PARSE;
	}


	bool status = true;
	while (status){
		try{
			while (ifs) {
				isHorn();

				if (currentHorn->complete){
					dequeTP flat_dtp = currentHorn->flatten(true);
					hornClause.push_back(flat_dtp);
					currentPhrase.clear();
				}

				currentHorn.reset();
				advance();
				currentPhrase.push_front(scan->currentTkn);

			}
		}
		catch (string &s) {         
			if (scan->nextTkn != nullptr) {
				advance();
			}

			else status = false;
		}
        /////////////
        catch (ERRORS &e) {
            cout << "END caught in parse" << endl;
            status = false;
        }
        catch (...) {
            cout << "parse 2::unexpected error" << endl;
            return BAD_PARSE;
        }
        /////////////
        
	}    
	return NO_ERROR;
}

int semAnalysis(string &output) {
	
	ofstream ofs(output);
	if (!ofs) {
		cout << "Error: could not write to output file." << endl;
		return BAD_OF;
	}


	//-------LABELS------//
	deque<string> allLabels;
	deque<string> uniqueLabels;

	//-------ALL LABELS------//
	for (dequeTP d : hornClause) {
		for (tokenPtr token_itr : d) {
			if (token_itr->isLabel()) {
				allLabels.push_back(token_itr->str);
			}
		}
	}

	//-------UNIQUE LABELS------//
	for (string s : allLabels){
		if (find(uniqueLabels.begin(), uniqueLabels.end(), s) == uniqueLabels.end()) { 
			uniqueLabels.push_back(s);
		}
	}

	sort(uniqueLabels.begin(), uniqueLabels.end());
	for (string s : uniqueLabels) {
		ofs << s << endl;
	}
	ofs << endl << endl;
	

	//-------NUMS------//
	deque<double> allNums;
	deque<double> uniqueNums;

	//-------ALL NUMS------//
	for (dequeTP d : hornClause) {
		for (tokenPtr token_itr : d) {
			if (token_itr->isNumeric()) {
				allNums.push_back(stod(token_itr->str));
			}
		}
	}

	//-------UNIQUE NUMS------//
	for (double i : allNums){
		if (find(uniqueNums.begin(), uniqueNums.end(), i) == uniqueNums.end()) {
			uniqueNums.push_back(i);
		}
	}
	
	sort(uniqueNums.begin(), uniqueNums.end());
	for (double s : uniqueNums) {
		ofs << s << endl;
	}
	ofs << endl << endl;
	

	//-------HORN CLAUSE------//
	for (dequeTP d : hornClause) {
		for (tokenPtr token_itr : d){ 
			ofs << token_itr << " ";
		}
		ofs << endl;
	}

	return NO_ERROR;
}