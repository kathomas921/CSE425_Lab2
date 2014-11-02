#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "stdafx.h"
#include "entry.h"
#include <set>

struct symbolTable {
	set<entry> id;
	bool has(entry e);
	bool has(TERMINAL term, string str);
	void update(TERMINAL term, string str);
	tokenPtr getToken(TERMINAL term, string str);
};


#endif

