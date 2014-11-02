#ifndef ENTRY_H
#define ENTRY_H

#include "stdafx.h"
#include "token.h"

struct entry {
	string id;
	TERMINAL type;
	tokenPtr ref;

	entry();
	entry(string name);
	entry(TERMINAL type, string name);
	entry(TERMINAL type, string name,tokenPtr tkn);
	entry(TERMINAL type);

};

struct numEntry : public entry {
	unsigned int const val;
	//tokenPtr ref;

	numEntry();
	numEntry(string s);
	numEntry(string s,tokenPtr tkn);

};

struct labEntry : public entry {
	string val;
	//tokenPtr ref;

	labEntry();
	labEntry(string s);
	labEntry(string s, tokenPtr tkn);

};


#endif