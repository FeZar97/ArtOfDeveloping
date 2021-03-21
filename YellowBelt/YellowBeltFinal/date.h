#pragma once
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class Date {
	int year;
	int month;
	int day;

public:
	Date(int y = 0, int m = 1, int d = 1);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	friend bool operator<(const Date& lhs, const Date& rhs);
	friend bool operator>(const Date& lhs, const Date& rhs);
	friend bool operator==(const Date& lhs, const Date& rhs);
};

Date ParseDate(istringstream& is);