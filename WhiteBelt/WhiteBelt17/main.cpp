/*  ���� ������. ������� � ���� ������ ������ ��������� ����� f � �������� ������ ����� ���������. 
	���� ����� f � ������ ������ ����������� ������ ���� ���, �������� ����� -1, 
	� ���� �� ����������� �� ����, �������� ����� -2. ������� ���������� � ����.*/
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