/* Реализуйте класс ReversibleString, хранящий строку и поддерживающий методы Reverse для переворота строки и ToString для получения строки. */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class ReversibleString {
	string s;
public:
	ReversibleString() {};
	ReversibleString(string _s): s(_s) {}

	void Reverse() {
		for (int i = 0; i < s.length()/2; i++) {
			swap(s[i], s[s.length() - 1 - i]);
		}
	};

	string ToString() const {
		return s;
	};
};