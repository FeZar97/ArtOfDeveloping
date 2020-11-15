/*	� ���� ������ ��� ����� ����������� ������ ���������� ���������.
	� ������, ��� ������� ��������, ��������� ������� �������� ���������, 
	����� ���� ������ ����� ����� (������� �������� � 1, ������� � 2 � �. �.), 
	���� ������� ����� ������������� ��������, �������� ������������� ����� ����� ���������.

	������ ���������, ���������� ���� �� ����� ������������� ���������, ��������� ���������� (��. ������).

��������
   � C++ ������ ������� ����� ���� �� ������ ����� ��� ������, �� � ������ ���������, ��������, vector.

������ �����
	������� �������� ���������� �������� Q, ����� Q �������� ��������.
	������ ������ ������������ ����� ������������� ���������� ��������� N, �� ������� ������� ���������� 
	�������� N ��������� �������� ��������� ���������������� ��������. �������� ��������� ������� ���� �� 
	��������� ���� � �������� �������������.

������ ������
	�������� ����� �� ������ ������ � ��������� ������.
	���� ������� � ������ ������� ��������� ��� ����������, � ����� �� ��������������� ������ 
	�������� 'Already exists for i', ��� i � ����� �������� � ����� ������� ���������. 
	� ��������� ������ ����� �������� ��������� ������ ��������� ����� ����� i � ������� ��� � ������� 'New bus i'.
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
	int queryNb, stopsNb;
	map<vector<string>, int> routes;
	vector<string> tempRoute;

	cin >> queryNb;

	for (int i = 0; i < queryNb; i++) {
		cin >> stopsNb;
		tempRoute.assign(stopsNb, "");
		for (int j = 0; j < stopsNb; j++) {
			cin >> tempRoute[j];
		}

		if (routes.count(tempRoute)) {
			cout << "Already exists for " << (*(routes.find(tempRoute))).second << endl;
		}
		else {
			int busNumber = routes.size() + 1;
			routes[tempRoute] = busNumber;
			cout << "New bus " << busNumber << endl;
		}
	}

	return 0;
}