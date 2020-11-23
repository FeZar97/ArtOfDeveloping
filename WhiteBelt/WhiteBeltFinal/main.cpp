#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

class Date {
	int year;
	int month;
	int day;

public:
	int GetYear() const {
		return year;
	}

	int GetMonth() const {
		return month;
	}

	int GetDay() const {
		return day;
	}

	friend bool operator<(const Date& lhs, const Date& rhs) {
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

	friend stringstream& operator>>(stringstream &ss, Date &date) {
		string error_message = "", temp;
		int _year, _month, _day;
		char _delim1, _delim2;

		ss >> _year >> _delim1 >> _month >> _delim2 >> _day;
		if (_delim1 != '-' || _delim2 != '-' || !ss.good() || (ss.peek() != ' ' && ss.peek() != '\n')) {
			// error_message = "Wrong date format: " + to_string(_year) + _delim1 + to_string(_month) + _delim2 + to_string(_day);
			error_message = "Wrong date format: " + ss.str();
		}
		else {
			if (_month > 0 && _month < 13) {
				if (_day > 0 && _day < 32) {
					date.year  = _year;
					date.month = _month;
					date.day   = _day;
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
		return ss;
	}
};

class Database {

	map<Date, set<string>> db;

public:
	void AddEvent(const Date& date, const string& event) {
		db[date].insert(event);
	}

	bool DeleteEvent(const Date& date, const string& event) {
		if (db.count(date)) {
			return db.at(date).erase(event);
		}
		else {
			return false;
		}
	}

	int DeleteDate(const Date& date) {
		int size = 0;
		if (db.count(date)) {
			size = db.at(date).size();
			db.erase(date);
		}
		return size;
	}

	set<string> Find(const Date& date) const {
		if (db.count(date)) {
			return db.at(date);
		}
		else {
			return {};
		}
	}

	void Print() const {
		for (auto record : db) {
			for (auto event : record.second) {
				if (record.first.GetYear() >= 0) {
					cout.fill('0');
					cout << setw(4) << record.first.GetYear()  << "-"
						 << setw(2) << record.first.GetMonth() << "-" 
						 << setw(2) << record.first.GetDay()   << " "
						 << event << endl;
				}
			}
		}
	}
};

int main() {
	Database db;
	Date date;
	string line, command, event;
	stringstream ss;

	while (getline(cin, line)) {
		try {
			if (line.empty() || line == "\n") {
				continue;
			}
			ss.clear();
			ss << line;
			ss >> command;

			if (command == "Add") {
				ss >> date >> event;
				db.AddEvent(date, event);
			}
			else if (command == "Del") {
				ss >> date;

				if (ss.peek() == '\n' || ss.peek() == EOF) {
					int delEvNb = db.DeleteDate(date);
					cout << "Deleted " << delEvNb << " events" << endl;
				}
				else {
					ss >> event;
					if (db.DeleteEvent(date, event)) {
						cout << "Deleted successfully" << endl;
					}
					else {
						cout << "Event not found" << endl;
					}
				}
			}
			else if (command == "Find") {
				ss >> date;
				auto dateEvent = db.Find(date);
				for (auto event : dateEvent) {
					cout << event << endl;
				}
			}
			else if (command == "Print") {
				db.Print();
			}
			else {
				cout << "Unknown command: " + command << endl;
				break;
			}
		}
		catch (exception &ex) {
			cout << ex.what() << endl;
			break;
		}
	}

	/*
	stringstream ss;
	ss << "Add 1-2-3 event1";
	cout << "ss state: " << ss.str() << endl;


	string command;
	ss >> command;

	char nextSym = ss.peek();

	cout << "nextSym: " << nextSym << endl;
	cout << "ss state: " << ss.str() << endl;

	*/
	system("pause");

	return 0;
}