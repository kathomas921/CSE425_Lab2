//derivedToken.cpp
//Katharine Thomas & James Wilson
//
//Constructors for the label and number derived structs

#include "stdafx.h"
#include "derivedToken.h"

#include <sstream>

label::label(string const &s) : token(LABEL,s){}

number::number(string const &s) : token(NUMBER,s) {
	istringstream iss(s);
	iss >> val;
}