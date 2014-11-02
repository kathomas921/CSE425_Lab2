//parse.h
//Katharine Thomas & James Wilson
//Prototype for functions in parse.cpp

#ifndef PARSE_H
#define PARSE_H

#include "stdafx.h"
#include "token.h"
#include <string>


using namespace std;

enum ERRORS{ NO_ERROR, BAD_IF, BAD_OF, BAD_PRED , BAD_PARSE, BAD_INPUT, END };


void
advance(),
expectNext(TERMINAL t),
isSymbol(),
isName(),
isArgs(),
isPredicate(),
isBody(),
isHorn();


bool isKind(string kind, shared_ptr<token> tokenPtr);

//Implements recursive descent to determine if a clause is of the proper input grammer
int parse(string &input);

//Prints each properly formed Horn Clause as well as all unique labels and numbers within them
int semAnalysis(string &output);

#endif