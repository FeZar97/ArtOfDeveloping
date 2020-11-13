/*  ƒана строка. Ќайдите в этой строке второе вхождение буквы f и выведите индекс этого вхождени€. 
	≈сли буква f в данной строке встречаетс€ только один раз, выведите число -1, 
	а если не встречаетс€ ни разу, выведите число -2. »ндексы нумеруютс€ с нул€.*/
#include <iostream>
#include <string>

using namespace std;

int getSecondEntry(string s) {
	int first, second;
	first = s.find('f');
	second = s.find('f', first + 1);

	if (first == second) {
		if (first == string::npos) {
			return -2;
		}
		else {
			return -1;
		}
	}
	else {
		return second;
	}
};

int main() {
	string input;
	cin >> input;

	cout << getSecondEntry(input) << endl;

	return 0;
}