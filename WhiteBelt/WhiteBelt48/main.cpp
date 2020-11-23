/*	���������� ��������� �������� �� ���������� ������: ���, �������, ����, ����� � ��� ��������. 
	�������� ������ �� ����� ��������, ��������� ��� �� ������� ������ � ����� �� �������� �������� ������ ����.

	������ �����
	������ ������ �������� ���� ����� ����� N �� 0 �� 10000 � ����� ���������.
	����� ���� N �����, ������ �� ������� �������� ��� ������ ������ �� 1 �� 15 �������� � ��� � ������� 
	���������� ��������, � ��� ����� ����� �� 0 �� 1000000000 � ����, ����� � ��� ��������.
	��������� ������ �������� ���� ����� ����� M �� 0 �� 10000 � ����� ��������.
	��������� M ����� �������� ������ ������ �� 1 �� 15 �������� � ������, � ����� ����� �� 0 �� 1000000000 � ����� �������� (��������� ���������� � 1).

	������ ������
	��� ������� ���� name K, ��� K �� 1 �� N, �������� ����� ������ ��� � ������� K-�� ��������.
	��� ������� ���� date K, ��� K �� 1 �� N, �������� ����� ����� ����, ����� � ��� �������� K-�� ��������.
	��� ��������� �������� �������� bad request. */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
	string firstName;
	string secondName;
	int day;
	int month;
	int year;
};

int main() {
	vector<Student> students;
	Student tempStudent;
	int n, m, k;
	string requestType;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> tempStudent.firstName >> tempStudent.secondName >> tempStudent.day >> tempStudent.month >> tempStudent.year;
		students.push_back(tempStudent);
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> requestType >> k;

		if (requestType == "name") {
			if (k < 1 || k > students.size()) {
				cout << "bad request" << endl;
			}
			else {
				cout << students[k - 1].firstName << " " << students[k - 1].secondName << endl;
			}
		}
		else if (requestType == "date") {
			if (k < 1 || k > students.size()) {
				cout << "bad request" << endl;
			}
			else {
				cout << students[k - 1].day << "." << students[k - 1].month << "." << students[k - 1].year << endl;
			}
		}
		else {
			cout << "bad request" << endl;
		}
	}

	return 0;
}