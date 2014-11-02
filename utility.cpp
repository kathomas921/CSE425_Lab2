
#include "stdafx.h"
#include "utility.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>


using namespace std;

static deque<string> indentation;

void indent(){
	copy(indentation.begin(), indentation.end(), ostream_iterator<string>(cout));
}

void calls(string lhs, string rhs, int direction){
	indent();
	if (direction>0){
		cout << lhs << "() --> " << rhs << "()" << endl;
		indentation.push_back("");
	}
	else{
		cout << rhs << "() -- > " << lhs << "()" << endl;
		indentation.pop_back();
	}
};

void calls(string lhs, string rhs, int lineNumber, int direction){
	indent();
	if (direction>0){
		cout << lhs << "() --> " << rhs << "() @ln. " << lineNumber << endl;
		indentation.push_back("   ");
	}
	else{
		cout << rhs << "() -- > " << lhs << "() @ln. " << lineNumber << endl;
		indentation.pop_back();
	}
};

void cprintl(string str){
	indent();
	cout << str << endl;
}

void cprint(string str){
	indent();
	cout << str;
}
