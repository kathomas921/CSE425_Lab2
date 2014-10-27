//phrase.h
//Katharine Thomas & James Wilson
//Prototype for functions in phrase.cpp


#ifndef phrase_h
#define phrase_h


#include "stdafx.h"
#include "token.h"
#include "derivedToken.h"
#include <deque>

using namespace std;


enum POS { posX, NAME, SYMB, PRED, BODY, HEAD, HORN};

string pos2str(POS id);

struct phrase {
	POS pos;
	bool complete;
	
	phrase();
	phrase(POS id);
	phrase(POS id, bool status);

	//virtual void print() = 0; to do

	virtual dequeTP flatten(bool format) = 0;
	
	
};

typedef shared_ptr<phrase> phrasePtr;


string getPOS(const phrase & p);

struct name : phrase { 
	tokenPtr t; 
	name();
	name(tokenPtr tkn);

	friend ostream &operator<<(ostream &out, name n);

	virtual dequeTP flatten(bool format);
};


typedef shared_ptr<name> namePtr;

struct symb : phrase { 
	tokenPtr t;
	symb();
	symb(tokenPtr t);

	friend ostream &operator<<(ostream &out, symb s);

	virtual dequeTP flatten(bool format);
};

typedef shared_ptr<symb> symbPtr;
typedef deque<symbPtr> symbD;

struct pred : phrase {
	namePtr n;
	symbD s;

	pred();
	pred(namePtr n);
	pred(symbD s);
	pred(namePtr n, bool status);
	pred(symbD s, bool status);
	pred(namePtr n, symbD s);
	pred(namePtr n, symbD s, bool status);

	friend ostream &operator<<(ostream &out,pred p);

	virtual dequeTP flatten(bool format);

};

typedef shared_ptr<pred> predPtr;
typedef deque<predPtr> predD;

struct body : phrase {
	predD p;

	body();
	body(predD p);
	body(predD p, bool status);

	friend ostream &operator<<(ostream &out, body b);

	virtual dequeTP flatten(bool format);
};

typedef shared_ptr<body> bodyPtr;

struct head : phrase {
	predPtr p; 
	
	head();
	head(predPtr p);

	friend ostream &operator<<(ostream &out, head h);

	virtual dequeTP flatten(bool format);

};
typedef shared_ptr<head> headPtr;

struct horn : phrase { 
	headPtr h;
	bodyPtr b; 

	horn();
	horn(headPtr h);
	horn(bodyPtr b);
	horn(headPtr h, bool status);
	horn(bodyPtr b, bool status);
	horn(headPtr h, bodyPtr b);

	friend ostream &operator<<(ostream &out, horn h);

	virtual dequeTP flatten(bool format);
};

typedef shared_ptr<horn> hornPtr;

#endif