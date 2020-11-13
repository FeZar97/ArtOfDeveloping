/*  В stdin даны два натуральных числа. Выведите в stdout их наибольший общий делитель.*/
#include <iostream>

using namespace std;

int main() {
	int a, b, gcd;
	cin >> a >> b;

	while (true) {
		if (a == b ) {
			gcd = a;
			break;
		}
		else if (a == 1 || b == 1) {
			gcd = 1;
			break;
		}
		else if(a == 0) {
			gcd = b;
			break;
		}
		else if (b == 0) {
			gcd = a;
			break;
		}
		else if (a > b) {
			a -= (a / b) * b;
		}
		else {
			b -= (b / a) * a;
		}
	}

	cout << gcd << endl;

	return 0;
}