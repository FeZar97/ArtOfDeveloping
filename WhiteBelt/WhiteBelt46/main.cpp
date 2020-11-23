/*	� ����� input.txt �������� ������������ �����, �� ������ �� �������. 
	�� ����������� ����� ����������� ��� ����� � ��� �� �������, �� ������ �� ������, 
	�� �������� ���, ����� � ������� �� ��� ���� ����� ��� ����� ����� ���������� �����. */
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
	ifstream is("input.txt");
	cout << fixed << setprecision(3);
	double val;

	while (is >> val) {
		cout << val << endl;
	}

	return 0;
}