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

	friend istream& operator>>(istream &is, Date &date) {
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
		// if (!ss.eof()) { // || (!ss.good() && !ss.eof())) {
		// 	error_message = "Wrong date format: " + inputString;
		// }

		if (ss.peek() != EOF) {
			error_message = "Wrong date format: " + inputString;
		}

		if (error_message.empty()) {
			if (_month > 0 && _month < 13) {
				if (_day > 0 && _day < 32 && ss.eof()) {
					date.year = _year;
					date.month = _month;
					date.day = _day;
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
		return is;
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

vector<pair<string, string>> Tests{
	{"Add 1-1- event0", "Wrong date format: 1-1-\n"},
	{"Add 1-1-t event1", "Day value is invalid: 0\n"},
	{"Add 1-1-1) event2", "Wrong date format: 1-1-1)\n"},
	{"Add 1-t-1 event3", "Wrong date format: 1-t-1\n"},
	{"Add t-1-1 event4", "Wrong date format: t-1-1\n"},
	{"Add 1--1-+1 event5", "Month value is invalid: -1\n"},
	{"Add -1--1-+1 event6", "Month value is invalid: -1\n"},
	{"Add -1--1--1 event7", "Month value is invalid: -1\n"},
	{"Add -1-+1--1 event8", "Day value is invalid: -1\n"},
	{"Add -1-+13--1 event9", "Month value is invalid: 13\n"},
	{"Add -1-+12-32 event10", "Day value is invalid: 32\n"},
	{"Add -1-+12-+32 event11", "Day value is invalid: 32\n"},
	{"Add 1-1-1- event12", "Wrong date format: 1-1-1-\n"},
	{"Add 1-1-+t event14", "Day value is invalid: 0\n"},
	{"Add 1-1--t event14", "Day value is invalid: 0\n"},

	{"Add 1-1-1 1event", ""},
	{"Add 1-1-+1 2event", ""},
	{"Add -1-+1-+1 3event", ""},
	{"Add -1-+1-+1 4event", ""},
};

int CoreFunction(string input, string &answer) {
	Database db;
	Date date;
	string line = input, command, event;
	stringstream ss, answerstream;

	try {
		if (line.empty() || line == "\n") {
			answer = "";
			return 0;
		}
		ss.clear();
		ss << line;
		ss >> command;

		if (command == "Add") {
			ss >> date >> event;
			db.AddEvent(date, event);
			answer = "";
			return 0;
		}
		else if (command == "Del") {
			ss >> date;

			if (ss.peek() == '\n' || ss.peek() == EOF) {
				int delEvNb = db.DeleteDate(date);
				answerstream << "Deleted " << delEvNb << " events" << endl;
				answer = answerstream.str();
				return 0;
			}
			else {
				ss >> event;
				if (db.DeleteEvent(date, event)) {
					answerstream << "Deleted successfully" << endl;
					answer = answerstream.str();
					return 0;
				}
				else {
					answerstream << "Event not found" << endl;
					answer = answerstream.str();
					return 0;
				}
			}
		}
		else if (command == "Find") {
			ss >> date;
			auto dateEvent = db.Find(date);
			for (auto event : dateEvent) {
				answerstream << event << endl;
			}
			answer = answerstream.str();
			return 0;
		}
		else if (command == "Print") {
			db.Print();
			answer = "";
			return 0;
		}
		else {
			answerstream << "Unknown command: " + command << endl;
			answer = answerstream.str();
			return -1;
		}
	}
	catch (exception &ex) {
		answerstream << ex.what() << endl;
		answer = answerstream.str();
		return -1;
	}
}


int main() {

	/*
	for (size_t i = 0; i < Tests.size(); i++) {
		string answer;
		int result = CoreFunction(Tests[i].first, answer);
		if (answer != Tests[i].second) {
			cout << "Error in test #" << i << "\n\t" << answer << "\t" << Tests[i].second << endl;
		}
	}
	*/

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

	return 0;
}