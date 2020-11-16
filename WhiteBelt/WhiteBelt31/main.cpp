/*	� ����������� ������ ���� ���� ������, ��������� �� N + 1 ����� �����. 
	������ ������ ��� ���� ����� N. ����� ������� ��� N �����, ��������� �� �� ������ A. 
	����� ����� ����� ��������� ��������.
	������������ ������ � �� ������ � �������� ��� � ����������� �����. */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	vector<int> v;

	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	sort(v.begin(), v.end(), [](int a, int b) {
		return abs(a) < abs(b);
	});

	for (auto i: v) {
		cout << i << " ";
	}

	return 0;
}