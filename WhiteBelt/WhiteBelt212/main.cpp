/* ���������� ���������� ������ �����.
	�� ���� ��������� ��������� ��������� �������:
		CHANGE_CAPITAL country new_capital � ��������� ������� ������ country �� new_capital, 
											 ���� ���������� ����� ������ � ����� ��������, ���� ������ � �� ����.
		RENAME old_country_name new_country_name � �������������� ������ �� old_country_name � new_country_name.
		ABOUT country � ����� ������� ������ country.
		DUMP � ����� ������ ���� �����.

������ �����
	� ������ ������ ���������� ���������� �������� Q, � ��������� Q ������� � �������� ��������. 
	��� �������� ����� � ������ ������� ���� �� ��������� ����, ���� � �������� �������������.

������ ������
	�������� ��������� ��������� ������� �������:

� ����� �� ������ CHANGE_CAPITAL country new_capital ��������
	- Introduce new country country with capital new_capital, ���� ������ country ������ �� ������������;
	- Country country hasn't changed its capital, ���� ������ country �� �������� ������� ����� ������� new_capital;
	- Country country has changed its capital from old_capital to new_capital, ���� ������ country �� �������� 
	  ������� ����� ������� old_capital, �������� ������� �� ��������� � ��������� new_capital.

� ����� �� ������ RENAME old_country_name new_country_name ��������
	- Incorrect rename, skip, ���� ����� �������� ������ ��������� �� ������, 
	  ������ old_country_name �� ���������� ��� ������ new_country_name ��� ����������;
	- Country old_country_name with capital capital has been renamed to new_country_name, 
	  ���� ������ ��������� � ������ ����� ������� capital.

� ����� �� ������ ABOUT country ��������
	- Country country doesn't exist, ���� ������ � ��������� country �� ����������;
	- Country country has capital capital, ���� ������ country ���������� � ����� ������� capital.

� ����� �� ������ DUMP ��������
	- There are no countries in the world, ���� ���� �� ���� ��������� �� ����� ������;
	- ������������������ ��� ���� country/capital, ����������� ������� ���� �����, 
	���� � ���� ��� ���� ���� �� ���� ������. ��� ������ ������������������ ���� ���������� 
	���� ���������� ����������� �� �������� ������ � ��������� ����� ����� ��������. */

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	int q;
	string command, temp1, temp2;
	map<string, string> countries;

	cin >> q;

	for (int i = 0; i < q; i++) {
		cin >> command;

		if (command == "CHANGE_CAPITAL") {
			cin >> temp1 >> temp2;
			if (countries.count(temp1) == 0) {
				cout << "Introduce new country " << temp1 << " with capital " << temp2 << endl;
				countries[temp1] = temp2;
			}
			else {
				if (countries[temp1] == temp2) {
					cout << "Country " << temp1 << " hasn't changed its capital" << endl;
				}
				else {
					cout << "Country " << temp1 << " has changed its capital from " << countries[temp1] << " to " << temp2 << endl;
					countries[temp1] = temp2;
				}
			}
		} else if (command == "RENAME") {
			cin >> temp1 >> temp2;
			if ( (countries.count(temp1) == 0) || countries.count(temp2) || (temp1 == temp2) ) {
				cout << "Incorrect rename, skip" << endl;
			}
			else {
				cout << "Country " << temp1 << " with capital " << countries[temp1] << " has been renamed to " << temp2 << endl;
				countries[temp2] = countries[temp1];
				countries.erase(temp1);
			}

		} else if(command == "ABOUT") {
			cin >> temp1;
			if (countries.count(temp1) == 0) {
				cout << "Country " << temp1 << " doesn't exist" << endl;
			}
			else {
				cout << "Country " << temp1 << " has capital " << countries[temp1] << endl;
			}
		}
		else if (command == "DUMP") {
			if (countries.empty()) {
				cout << "There are no countries in the world" << endl;
			}
			else {
				for (auto c : countries) {
					cout << c.first << "/" << c.second << endl;
				}
			}
		}
	}

	return 0;
}