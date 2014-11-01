//phrase.cpp
//Katharine Thomas & James Wilson
//
/*Defines the constructors for all of the part-of-speech (POS) structs.  The flatten methods when
used together properly construct a single deque of token ptrs representing the horn clause.
*/

//#include "stdafx.h"
#include "phrase.h"
#include <algorithm>
#include <iterator>

using namespace std;


//---------------------------------------------------------------- posID Method
string pos2str(POS id) {
	switch (id){
		case NAME:
			return "NAME";
		case SYMB:
			return "SYMB";
		case PRED:
			return "PRED";
		case BODY:
			return "BODY";
		case HEAD:
			return "HEAD";
		case HORN:
			return "HORN";
		default:
			return "posX";
	}
}


//---------------------------------------------------------------- Part of Speech (POS) Constructors

//-------------------------------- phrase Constructors
phrase::phrase() : pos(posX), complete(false)										{};
phrase::phrase(POS id) : pos(id), complete(false)									{};
phrase::phrase(POS id, bool status)	: pos(id), complete(status)						{};

//-------------------------------- name Constructors
name::name() : phrase(NAME), t()													{};
name::name(tokenPtr t) : phrase(NAME, true), t(t)									{};

//-------------------------------- symb Constructors
symb::symb() : phrase(SYMB), t()													{};
symb::symb(tokenPtr t) : phrase(SYMB, true), t(t)									{};

//-------------------------------- pred Constructors
pred::pred() : phrase(PRED), n(), s()												{ n = make_shared<name>(); s = deque<symbPtr>(); };
pred::pred(namePtr n) : phrase(PRED), n(n)											{ s = deque<symbPtr>(); };
pred::pred(symbD s) : phrase(PRED), s(s)											{ n = make_shared<name>(); };
pred::pred(namePtr n, bool status) : phrase(PRED, status), n(n)						{ s = deque<symbPtr>(); };
pred::pred(symbD s, bool status) : phrase(PRED, status), s(s)						{ n = make_shared<name>(); };
pred::pred(namePtr n, symbD s) : phrase(PRED), n(n), s(s)							{};
pred::pred(namePtr n, symbD s, bool status) : phrase(PRED, status), n(n), s(s)		{};

//-------------------------------- body Constructors
body::body() : phrase(BODY), p()													{ p = deque<predPtr>(); };
body::body(predD p) : phrase(BODY), p(p)											{};
body::body(predD p, bool status) : phrase(BODY, status), p(p)						{};

//-------------------------------- head Constructors
head::head() : phrase(HEAD), p()													{ p = make_shared<pred>(); };
head::head(predPtr p) : phrase(HEAD, true), p(p)									{};

//-------------------------------- horn Constructors
horn::horn() : phrase(HORN), h(), b()												{ h = make_shared<head>(); b = make_shared<body>(); };
horn::horn(headPtr h) : phrase(HORN), h(h)											{ b = make_shared<body>(); };
horn::horn(bodyPtr b) : phrase(HORN), b(b)											{ h = make_shared<head>(); };
horn::horn(headPtr h, bool status) : phrase(HORN, status), h(h)						{ b = make_shared<body>(); };
horn::horn(bodyPtr b, bool status) : phrase(HORN, status), b(b)						{ h = make_shared<head>(); };
horn::horn(headPtr h, bodyPtr b) : phrase(HORN), h(h), b(b)							{};




//---------------------------------------------------------------- phrasePOS Method
string getPOS(const phrase & p){
	return pos2str(p.pos);
};


//---------------------------------------------------------------- Flatten Methods

dequeTP name::flatten(bool format){
	dequeTP flat_dtp;
	flat_dtp.push_back(t);
	return flat_dtp;
}

dequeTP symb::flatten(bool format){
	dequeTP flat_dtp;
	flat_dtp.push_back(t);
	return flat_dtp;
}

dequeTP pred::flatten(bool format){
	dequeTP flat_dtp = n->flatten(false);
	for (symbPtr symb_itr : s){
		dequeTP symb_dtp = symb_itr->flatten(false);
		flat_dtp.insert(flat_dtp.end(), symb_dtp.begin(), symb_dtp.end());
	};

	if (format) {
		parenthesize(flat_dtp);
	}
	return flat_dtp;
}

dequeTP body::flatten(bool format){
	dequeTP flat_dtp;
	for (predPtr pred_itr : p){
		dequeTP pred_dtp = pred_itr->flatten(format);
		flat_dtp.insert(flat_dtp.end(), pred_dtp.begin(), pred_dtp.end());
	};
	if (flat_dtp.size() > 0 && format) parenthesize(flat_dtp);
	return flat_dtp;
}

dequeTP head::flatten(bool format){
	dequeTP flat_dtp = p->flatten(format);
	return flat_dtp;
}

dequeTP horn::flatten(bool format){
	dequeTP flat_dtp = h->flatten(format);
	dequeTP body_dtp = b->flatten(format);
	flat_dtp.insert(flat_dtp.end(), body_dtp.begin(), body_dtp.end());
	if (format) parenthesize(flat_dtp);
	return flat_dtp;
}


//---------------------------------------------------------------- ostream Insertion Operators

// ostream &operator<<(ostream &out, name n){
// 	out << &(getPOS(n)); // correctness?	
// 	return out;
// };