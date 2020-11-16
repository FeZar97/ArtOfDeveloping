/*	� ����������� ������ ���� ���� ������, ��������� �� ����� N � ��������� �� ��� N ����� S. 
	����� ����� ����� � ������ ��������� ��������.
	������������ ������ S � ������������������ ������� �� �����������, 
	��������� ������� ����, � �������� �� � ����������� ����� ������. */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool cmpFnct(const char &a, const char &b) {
	return tolower(a) < tolower(b);
};

int main() {
	int n;
	string temp;

	cin >> n;
	vector<string> v(n);

	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	sort(v.begin(), v.end(), [=](string a, string b) {
		return lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(), cmpFnct);
	});

	for (auto i : v) {
		cout << i << " ";
	}

	return 0;
}