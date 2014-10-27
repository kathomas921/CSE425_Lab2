//token.cpp
//Katharine Thomas & James Wilson
//
/*The token struct defines the necessary characteristics of a token
(a set of white space delimited characters drawn from the input file) */

//#include "stdafx.h"

#include "token.h"
#include <algorithm>
#include <string>
#include "utility.h"


token::token() : kind(UNKNOWN), str("") {}
token::token(string s) : kind(UNKNOWN), str(s){}
token::token(TERMINAL t, string const& s) : kind(t), str(s) {}

ostream &operator<<(ostream &out, tokenPtr t){
	out << t->str;
	return out;
}

ostream &operator<<(ostream &out, token t){
	out << t.str;
	return out;
}

bool token::isLabel(){
	bool result = (!str.empty() && (count_if(str.begin(), str.end(), ::isalpha) == str.size()));
	return result;
}


bool token::isLeftParen() {
	bool result = false;
	if (str == "(") {
		return true;
	}
	return result;
}

bool token::isRightParen() {
	bool result = false;
	if (str == ")") {
		result = true;
	}
	return result;
}

bool token::isComma() {
	bool result = false;
	if (str == ",") {
		result = true;
	}
	return result;
}

bool token::isNumeric() {
	bool result = (!str.empty() && (count_if(str.begin(), str.end(), ::isdigit) == str.size()));
	return result;
}

bool token::isAnd() {
	bool result = false;
	if (str == "^") {
		result = true;
	}
	return result;
}

bool token::isSep() {
	bool result = false;
	if (str == ":-") {
		return true;
	}
	return result;
}

void parenthesize(dequeTP & dtp){
	dtp.push_front(make_shared<token>(LEFTPAREN, "("));
	dtp.push_back(make_shared<token>(RIGHTPAREN, ")"));
}

string terminal_to_string(TERMINAL t) {

	if (t == AND) {
		return "AND";
	}
	if (t == LABEL) {
		return "LABEL";
	}
	if (t == NUMBER) {
		return "NUMBER";
	}
	if (t == LEFTPAREN) {
		return "LEFTPAREN";
	}
	if (t == RIGHTPAREN) {
		return "RIGHTPAREN";
	}
	if (t == SEPARATOR) {
		return "SEPARATOR";
	}
	if (t == COMMA) {
		return "COMMA";
	}
	else {
		return "UNKNOWN";
	}
}