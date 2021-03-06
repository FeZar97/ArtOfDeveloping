﻿/*	Реализуйте класс для человека, поддерживающий историю изменений человеком своих фамилии и имени.
	
	class Person {
	public:
	  void ChangeFirstName(int year, const string& first_name) {
	    // добавить факт изменения имени на first_name в год year
	  }
	  void ChangeLastName(int year, const string& last_name) {
	    // добавить факт изменения фамилии на last_name в год year
	  }
	  string GetFullName(int year) {
	    // получить имя и фамилию по состоянию на конец года year
	  }
	private:
	  // приватные поля
	};

	Считайте, что в каждый год может произойти не более одного изменения фамилии и не более одного изменения имени. 
	При этом с течением времени могут открываться всё новые факты из прошлого человека, поэтому года́ в последовательных 
	вызовах методов ChangeLastName и ChangeFirstName не обязаны возрастать.

	Гарантируется, что все имена и фамилии непусты.
	
	Строка, возвращаемая методом GetFullName, должна содержать разделённые одним пробелом имя и фамилию человека по состоянию на конец данного года.
	
	Если к данному году не случилось ни одного изменения фамилии и имени, верните строку "Incognito".
	Если к данному году случилось изменение фамилии, но не было ни одного изменения имени, верните "last_name with unknown first name".
	Если к данному году случилось изменение имени, но не было ни одного изменения фамилии, верните "first_name with unknown last name". */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Person {
	map<int, string> firstNameChanges;
	map<int, string> secondNameChanges;
public:
	void ChangeFirstName(int year, const string& first_name) {
		firstNameChanges.insert({ year, first_name });
	}
	void ChangeLastName(int year, const string& last_name) {
		secondNameChanges.insert({ year, last_name });
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
};