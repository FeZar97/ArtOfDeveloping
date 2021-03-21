#include "database.h"

void Database::Add(const Date& date, const string& event) {
	vector<string> curEvents = db[date];
	if (find(curEvents.begin(), curEvents.end(), event) == curEvents.end()) {
		db[date].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for (auto &record : db) {
		for (auto &event : record.second) {
			if (record.first.GetYear() >= 0) {
				os.fill('0');
				os << setw(4) << record.first.GetYear() << "-"
					<< setw(2) << record.first.GetMonth() << "-"
					<< setw(2) << record.first.GetDay() << " "
					<< event << endl;
			}
		}
	}
}

int Database::RemoveIf(bool* functor(const Date& date, const string& event)) {

	for (auto &dbPair : db) {
		auto& curDate = dbPair.first;
		if (functor(curDate, "")) {

		}
	}




	return 0;
}

vector<string> Database::FindIf(bool* func()) {
	return vector<string>();
}

string Database::Last(const Date& date) {
	return string();
}

bool Database::DeleteEvent(const Date& date, const string& event) {
	if (db.count(date)) {
		// return db.at(date).erase(event);
		return true;
	}
	else {
		return false;
	}
}

int Database::DeleteDate(const Date& date) {
	int size = 0;
	if (db.count(date)) {
		size = db.at(date).size();
		db.erase(date);
	}
	return size;
}

vector<string> Database::Find(const Date& date) const {
	if (db.count(date)) {
		return db.at(date);
	}
	else {
		return {};
	}
}
