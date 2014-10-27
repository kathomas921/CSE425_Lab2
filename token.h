//token.h
//Katharine Thomas & James Wilson
//Prototype for functions of the tokenStruct struct

#ifndef TOKEN_H
#define TOKEN_H

//#include "stdafx.h"
#include <iostream>
#include <memory>
#include <deque>

using namespace std;

enum TERMINAL{ UNKNOWN, AND, COMMA, LABEL, LEFTPAREN, NUMBER, RIGHTPAREN, SEPARATOR, ENDOF};



struct token {
	TERMINAL kind;
	string str;
	token();
	token(string s);
	token(TERMINAL t, string const& s);

	bool isLabel();
	bool isNumeric();
	bool isLeftParen();
	bool isRightParen();
	bool isComma();
	bool isAnd();
	bool isSep();
};


typedef shared_ptr<token> tokenPtr;
typedef deque<tokenPtr> dequeTP;

void parenthesize(dequeTP & dtp);

ostream &operator<<(ostream &out, token t);
ostream &operator<<(ostream &out, tokenPtr t);

string terminal_to_string(TERMINAL t);

#endif