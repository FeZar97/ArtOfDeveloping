/* �� ���� ���� ����� ������������� ����� N. �������� ��� � �������� ������� ��������� ��� ������� �����. */
#include <iostream>

using namespace std;

int main() {
	int n, currentPow = 31;
	bool started = false;
	cin >> n;

	while (currentPow >= 0) {
		if (n & (1 << currentPow)) {
			started = true;
			cout << 1;
		}
		else if(started) {
			cout << 0;
		}
		currentPow--;
	}

	return 0;
}