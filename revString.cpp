#include <iostream>
#include <string>

using namespace std;

bool isDelimeter(char c) {
	//if it's not a letter, number, or apostrophe
	if (!isalpha(c) && !isdigit(c) && (c!='\'')) {
		return true;
	}
	return false;
}


void flipString(string &s, int start, int end) {
	while (start < end) {
		char temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		++start;
		--end;
	}
}

int main (int argc, char* argv[]) {
	string s = ".I'm getting a new pooper-scooper. Yay!";
	cout << s << endl;
	flipString(s, 0, s.length()-1);

	int start = 0;
	int end;
	for (int i = 0; i <= s.length(); ++i) {
		if (isDelimeter(s[i])) {
			end = i-1;
			flipString(s, start, end);
			start = i+1;
		}
	}
	cout << s << endl;
	return 0;


	// string s = "I'm getting a new pooper-scooper. Yay!";
	// istringstream iss(s);
	// string word;
	// deque<string> rev;
	// string newS;
	// while (getline(iss >> word) {
	// 	rev.push_front(word);
	// 	newS = word + " " + newS;
	// }
	// copy(rev.begin(), rev.end(), ostream_iterator<string>(cout, " "));
	// cout << endl;
	// cout << endl << "new S : " << newS << endl;
}