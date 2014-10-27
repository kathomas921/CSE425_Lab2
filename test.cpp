#include <iostream>
#include <typeinfo>

using namespace std;

struct classname {
	void name() {cout << typeid(*this).name() << endl;}

};

int main(int argc, char* argv[]) {
	classname n;
	n.name();
	return 0;
}