//derivedToken.h
//Katharine Thomas & James Wilson
//Prototype for structs derived from the token struct

#ifndef DERIVEDTOKEN_H
#define DERIVEDTOKEN_H

#include "stdafx.h"
#include "token.h"

struct label : public token {
	label(string const &s);
};

struct number : public token {
	unsigned int val;
	number(string const &s);
};

#endif