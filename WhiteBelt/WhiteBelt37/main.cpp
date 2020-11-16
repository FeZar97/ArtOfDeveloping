/*	ƒополните класс Person из задачи Ђ»мена и фамилии Ч 2ї конструктором, позвол€ющим задать им€ и фамилию 
	человека при рождении, а также сам год рождени€.  ласс не должен иметь конструктора по умолчанию.
	ѕри получении на вход года, который меньше года рождени€:
		- методы GetFullName и GetFullNameWithHistory должны отдавать "No person";
		- методы ChangeFirstName и ChangeLastName должны игнорировать запрос.
	 роме того, необходимо объ€вить константными все методы, которые по сути ими €вл€ютс€.*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Person {
	int birthYear;
	map<int, string> firstNameChanges;
	map<int, string> secondNameChanges;

	Person();

	string Print(const vector <string> &vec) const {
		string answer = vec[0];

		if (vec.size() > 1) {
			answer += " (";
			for (int i = 1; i < vec.size(); i++) {
				answer += vec[i] + ((i < vec.size() - 1) ? ", " : "");
			}
			answer += ")";
		}

		return answer;
	};

public:
	Person(const string &first_name, const string &last_name, int year) {
		birthYear = year;
		firstNameChanges[year] = first_name;
		secondNameChanges[year] = last_name;
	}

	void ChangeFirstName(int year, const string& first_name) {
		if (year >= birthYear) {
			firstNameChanges[year] = first_name;
		}
	}

	void ChangeLastName(int year, const string& last_name) {
		if (year >= birthYear) {
			secondNameChanges[year] = last_name;
		}
	}

	string GetFullName(int year) const {

		if (firstNameChanges.empty() || year < birthYear) {
			return "No person";
		}

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
	string GetFullNameWithHistory(int year) const {

		if (firstNameChanges.empty() || year < birthYear) {
			return "No person";
		}

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