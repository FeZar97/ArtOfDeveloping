/* Дано два целых числа A и B (A <= B, A >= 1, B <= 30000). Выведите через пробел все чётные числа от A до B (включительно). */
#include <iostream>

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	for (int i = (a % 2 ? a + 1 : a); i <= b; i += 2) {
		cout << i << " ";
	}

	return 0;
}