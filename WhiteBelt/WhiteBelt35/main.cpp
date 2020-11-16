/*	��������� ����� �� ���������� ������ ������ � ������� � 1� ������� GetFullNameWithHistory

	class Person {
	public:
	  void ChangeFirstName(int year, const string& first_name) {
	    // �������� ���� ��������� ����� �� first_name � ��� year
	  }
	  void ChangeLastName(int year, const string& last_name) {
	    // �������� ���� ��������� ������� �� last_name � ��� year
	  }
	  string GetFullName(int year) {
	    // �������� ��� � ������� �� ��������� �� ����� ���� year
	  }
	  string GetFullNameWithHistory(int year) {
	    // �������� ��� ����� � ������� �� ��������� �� ����� ���� year
	  }
	private:
	  // ��������� ����
	};

	� ������� �� ������ GetFullName, ����� GetFullNameWithHistory ������ ������� �� ������ ��������� ��� � ������� 
	� ����� ������� ����, �� ��� � ��� ���������� ����� � ������� � �������� ��������������� �������. 
	���� ������� ����� ������� � ���, ��� ������� ��� ���� ������ ������� ������� ��� ��� �� ���� � �� ��, ������ ��������� 
	��� ������������ ������� ����� ������������. */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Person {
	map<int, string> firstNameChanges;
	map<int, string> secondNameChanges;

	string Print(const vector <string> &vec) {
		string answer = vec[0];

		if (vec.size() > 1) {
			answer += " (";
			for (int i = 1; i < vec.size(); i++) {
				answer += vec[i] + ( (i < vec.size() - 1) ? ", ": "");
			}
			answer += ")";
		}

		return answer;
	};

public:
	void ChangeFirstName(int year, const string& first_name) {
		firstNameChanges[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		secondNameChanges[year] = last_name;
	}
	string GetFullName(int year) {
		string firstName = "", secondName = "";

		// find firstName
		for (const auto &change : firstNameChanges) {
			if (change.first <= year) {
				firstName = change.second;
			}
			else {
				break;
			}
		}

		// find secondName
		for (const auto &change : secondNameChanges) {
			if (change.first <= year) {
				secondName = change.second;
			}
			else {
				break;
			}
		}

		if (!firstName.empty() && !secondName.empty()) {
			return firstName + " " + secondName;
		}
		else if (firstName.empty() && !secondName.empty()) {
			return secondName + " with unknown first name";
		}
		else if (!firstName.empty() && secondName.empty()) {
			return firstName + " with unknown last name";
		}
		else {
			return "Incognito";
		}
	}
	string GetFullNameWithHistory(int year) {

		vector<string> firstName, secondName;

		// select firstName
		for (const auto &change : firstNameChanges) {
			if (change.first <= year) {
				if (!firstName.empty()) {
					if (firstName[0] != change.second) {
						firstName.insert(firstName.begin(), change.second);
					}
				}
				else {
					firstName.insert(firstName.begin(), change.second);
				}
			}
			else {
				break;
			}
		}

		// find secondName
		for (const auto &change : secondNameChanges) {
			if (change.first <= year) {
				if (!secondName.empty()) {
					if (secondName[0] != change.second) {
						secondName.insert(secondName.begin(), change.second);
					}
				}
				else {
					secondName.insert(secondName.begin(), change.second);
				}
			}
			else {
				break;
			}
		}

		if (!firstName.empty() && !secondName.empty()) {
			return Print(firstName) + " " + Print(secondName);
		}
		else if (firstName.empty() && !secondName.empty()) {
			return Print(secondName) + " with unknown first name";
		}
		else if (!firstName.empty() && secondName.empty()) {
			return Print(firstName) + " with unknown last name";
		}
		else {
			return "Incognito";
		}
	}
};