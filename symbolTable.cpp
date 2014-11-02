#include "stdafx.h"
#include "entry.h"
#include "symbolTable.h"
#include "derivedToken.h"


using namespace std;

symbolTable::symbolTable() : id() {};

bool symbolTable::has(entry e){
	return id.find(e) != id.end();
}


bool symbolTable::has(TERMINAL term, string str){
	return id.find(entry(term,str)) != id.end();
}


void symbolTable::update(TERMINAL term, string str){

	switch (term)
	{

	case NUMBER:

		if (!has(term, str)){
			numEntry ent(str, make_shared<number>(str));
			id.insert(ent);}
		break;

	case LABEL:
		if (!has(term, str)){
			labEntry ent(str, make_shared<label>(str));
			id.insert(ent);}
		break;
	
	case LEFTPAREN:
		if (!has(term, str)){
			labEntry ent(str, make_shared<token>(term,str));
			id.insert(ent);
		}
		break;

	case RIGHTPAREN:
		if (!has(term, str)){
			labEntry ent(str, make_shared<token>(term, str));
			id.insert(ent);
		}
		break;

	}
}

tokenPtr symbolTable::getToken(TERMINAL term, string str){
	return (*(id.find(entry(term, str)))).ref;
}