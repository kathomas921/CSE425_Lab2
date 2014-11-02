#include "stdafx.h"
#include "entry.h"
#include <sstream>

using namespace std;

unsigned int str2uint(string s){
	unsigned int val;
	istringstream temp(s);
	temp >> val;
	return val;
}

//-------------------------------- entry Constructors
entry::entry() : id(""), type(UNKNOWN),ref(nullptr)										{};
entry::entry(string name) : id(name), type(UNKNOWN), ref(nullptr)						{};
entry::entry(TERMINAL type, string name) : id(name), type(type), ref(nullptr)			{};
entry::entry(TERMINAL type) : id(""), type(type), ref(nullptr)							{};
entry::entry(TERMINAL type, string name, tokenPtr tkn) : id(name), type(type), ref(tkn)			{};




//-------------------------------- numEntry Constructors
numEntry::numEntry() : entry(NUMBER), val()									{};
numEntry::numEntry(string name) : entry(NUMBER, name), val(str2uint(name))	{};
numEntry::numEntry(string name, tokenPtr tkn) : entry(NUMBER, name, tkn), val(str2uint(name)) {};

//-------------------------------- labEntry Constructors
labEntry::labEntry() : entry(LABEL), val()						{};
labEntry::labEntry(string name) : entry(LABEL, name), val(name)		{};
labEntry::labEntry(string name,tokenPtr tkn) : entry(LABEL, name,tkn), val(name) {};