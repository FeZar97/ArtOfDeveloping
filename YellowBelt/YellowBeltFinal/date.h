#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Date {
	int year;
	int month;
	int day;

public:
	Date(int y = 0, int m = 1, int d = 1);
	Date(const Date& otherDate);
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	friend bool operator<(const Date& lhs, const Date& rhs);
	friend bool operator>(const Date& lhs, const Date& rhs);
	friend bool operator==(const Date& lhs, const Date& rhs);
};

ostream& operator<< (ostream& out, const Date& date);

Date ParseDate(istream& is);