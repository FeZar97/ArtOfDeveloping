/*	��� ����� ���������� ���������� ���� �����, ���� ��� ����� ������� ��������. 
	���������� ��������� �������� ��� ������� ���������:
		- ADD word1 word2 � �������� � ������� ���� ��������� (word1, word2).
		- COUNT word � ������ ���������� ��������� ����� word.
		- CHECK word1 word2 � ���������, �������� �� ����� word1 � word2 ����������. 
		  ����� word1 � word2 ��������� ����������, ���� ����� �������� ADD ��� ���� 
		  �� ���� ������ ADD word1 word2 ��� ADD word2 word1.

	���������
		��� ���������, ����� �������, ��� �������� �� �������� ���������������, 
		�� ����, ���� A - ������� B, � B - ������� C, �� �� ����� �� �������, ��� A - ������� C.

	������ �����
		������� �������� ���������� �������� Q, ����� Q ����� � ���������� ��������. 
		�������������, ��� � ������ ������� CHECK � ADD ����� word1 � word2 ��������. 
		��� ����� ������� ���� �� ��������� ����, ���� � �������� �������������.

	������ ������
		��� ������� ������� � ��������������� ������ �������� ����� �� ����:
		- � ����� �� ������ COUNT word �������� ������������ ����� ����� � ���������� ��������� ����� word.
		- � ����� �� ������ CHECK word1 word2 �������� ������ YES, ���� word1 � word2 �������� ����������, � NO � ��������� ������. */
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

int main() {
	int queryNb;
	map<string, set<string>> synonims;
	string command, w1, w2;

	cin >> queryNb;
	for (int i = 0; i < queryNb; i++) {
		cin >> command;

		if (command == "ADD") {
			cin >> w1 >> w2;
			synonims[w1].insert(w2);
			synonims[w2].insert(w1);
		}
		else if (command == "COUNT") {
			cin >> w1;
			cout << synonims[w1].size() << endl;
		}
		else if (command == "CHECK") {
			cin >> w1 >> w2;
			bool isSyn = false;
			if (synonims[w1].count(w2) || synonims[w2].count(w1)) {
				isSyn = true;
			}
			cout << (isSyn ? "YES" : "NO") << endl;
		}
	}

	return 0;
}