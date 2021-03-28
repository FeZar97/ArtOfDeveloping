#include "date.h"

Date::Date(int y, int m, int d): year(y), month(m), day(d) {
}

Date::Date(const Date& otherDate) {
	year = otherDate.year;
	month = otherDate.month;
	day = otherDate.day;
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.year < rhs.year) {
		return true;
	}
	else if (lhs.year == rhs.year) {
		if (lhs.month < rhs.month) {
			return true;
		}
		else if (lhs.month == rhs.month) {
			if (lhs.day < rhs.day) {
				return true;
			}
		}
	}
	return false;
}

bool operator>(const Date& lhs, const Date& rhs) {
	if (lhs.year > rhs.year) {
		return true;
	}
	else if (lhs.year == rhs.year) {
		if (lhs.month > rhs.month) {
			return true;
		}
		else if (lhs.month == rhs.month) {
			if (lhs.day > rhs.day) {
				return true;
			}
		}
	}
	return false;
}

bool operator==(const Date& lhs, const Date& rhs) {
	if ((lhs.year == rhs.year) &&
		(lhs.month == rhs.month) &&
		(lhs.day == rhs.day) ) {
		return true;
	}
	return false;
}

ostream& operator<<(ostream& out, const Date& date) {

	if (date.GetYear() >= 0) {
		out.fill('0');
		out << setw(4) << date.GetYear() << "-"
			<< setw(2) << date.GetMonth() << "-"
			<< setw(2) << date.GetDay();
	}

	return out;
}

Date ParseDate(istream& is) {

	string error_message = "", inputString;
	int _year, _month, _day;
	char _delim1, _delim2;
	stringstream ss;

	is >> inputString;
	ss << inputString;

	ss >> _year;
	if (!ss.good() || ss.eof()) {
		error_message = "Wrong date format: " + inputString;
	}

	ss >> _delim1;
	if (!ss.good() || _delim1 != '-' || ss.eof()) {
		error_message = "Wrong date format: " + inputString;
	}

	ss >> _month;
	if (!ss.good() || ss.eof()) {
		error_message = "Wrong date format: " + inputString;
	}

	ss >> _delim2;
	if (!ss.good() || _delim2 != '-' || ss.peek() == EOF) {
		error_message = "Wrong date format: " + inputString;
	}

	ss >> _day;

	if (ss.peek() != EOF) {
		error_message = "Wrong date format: " + inputString;
	}

	if (error_message.empty()) {
		if (_month > 0 && _month < 13) {
			if (_day > 0 && _day < 32 && ss.eof()) {

				return Date(_year, _month, _day);
			}
			else {
				error_message = "Day value is invalid: " + to_string(_day);
			}
		}
		else {
			error_message = "Month value is invalid: " + to_string(_month);
		}
	}

	if (!error_message.empty()) {
		throw runtime_error(error_message);
	}

	return Date();
}
