/* ����� ���������� ����������� ���� �����, ���� ���� �� ��� ����� �������� �������������
	���� � ������. ��������, ����� �eat� ����� �������� ������������� ���� ����� �tea�,
	������� ��� ����� �������� ����������� ���� �����.

	���� ���� ����, ��������� ��� ������ �� ���, �������� �� ����� ���� ���� ����������� ���� �����.

��������
	���� �� �������� �������� ����, �������� �� ����� ����������� ���� �����, ����������� � ���������.
	��� ������� ����� � ������� ������� ����������, ������� ��� � ��� ����������� ������ �����.
	���� ��� ����� ���� ��� ������� ����� (� ��� ����������� � ������� �������� ��������� ==),
	�� ����� �������� ����������� ���� �����, � ��������� ������ �� ��������.

	��� ���� ���������� ������ ������� �� ����� ������ ������� � ��������� ������� BuildCharCounters.

������ �����
	������� ���� ����� ��� ���� N, ����� � N ������� ���������� ���� ����, ������� ���������� ���������.
	�������������, ��� ��� ����� ������� ���� �� �������� ��������� ����.

������ ������
	�������� N �����: ��� ������ �������� ���� ���� YES, ���� ��� ����� �������� �����������, � NO � ��������� ������. */

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<char, int> BuildCharCounters(string& word) {
	map<char, int> result;
	for (auto c : word) {
		result[c]++;
	}
	return result;
}

int main() {
	int pairsNb;
	string word1, word2;
	vector<bool> answer;
	cin >> pairsNb;

	for (int i = 0; i < pairsNb; i++) {
		cin >> word1 >> word2;
		answer.push_back(BuildCharCounters(word1) == BuildCharCounters(word2));
	}

	for (auto a : answer) {
		cout << (a ? "YES" : "NO") << endl;
	}

	return 0;
}