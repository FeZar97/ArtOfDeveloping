#include "database.h"

ostream& operator<<(ostream& out, const DbPair& dbPair) {
	if (dbPair.first.GetYear() >= 0) {
		out << dbPair.first << " " << dbPair.second;
	}

	return out;
}

void Database::Add(const Date& date, const string& event) {
	set<string> &curEvents = dbSet[date];

	auto insertResult = curEvents.insert(event);

	if (insertResult.second) {
		dates.insert(date);
		dbVec[date].push_back(event);
	}
}

void Database::Print(ostream& os) const {
	for (const pair<Date, vector<string>>&record : dbVec) {
		for (auto &event : record.second) {
			os << DbPair{record.first, event} << endl;
		}
	}
}

int Database::RemoveIf(function<bool(const Date& date_, const string& event_)> functor) {

	int removedElementsNb = 0;
	vector<Date> datesToDelete;

	for (pair<const Date, vector<string>> &dbPair: dbVec) {

		const Date& curDate = dbPair.first;
		vector<string>& events = dbPair.second;

		auto startIterToRemove = stable_partition(events.begin(), events.end(), 
			[&](const string& event__) {
				return !functor(curDate, event__);
			});

		removedElementsNb += distance(startIterToRemove, events.end());

		// if in result vector is empty - remove it from map
		if (startIterToRemove == events.begin()) {
			datesToDelete.push_back(curDate);
		}
		else {
			// remove from set
			// dbSet[curDate] = { events.begin(), events.end() };
			for (auto it = startIterToRemove; it != events.end(); it++) {
				dbSet[curDate].erase(*it);
			}

			// remove from vector
			events.erase(startIterToRemove, events.end());
		}
	}

	for (const Date& removedDate : datesToDelete) {
		dates.erase(removedDate);
		dbVec.erase(removedDate);
		dbSet.erase(removedDate);
	}

	return removedElementsNb;
}

vector<DbPair> Database::FindIf(function<bool(const Date& date_, const string& event_)> functor) const {
	vector<DbPair> result;

	for (const pair<const Date, vector<string>>& dbPair : dbVec) {

		const Date& curDate = dbPair.first;
		const vector<string>& events = dbPair.second;

		for (const string& curEvent : events) {
			if (functor(curDate, curEvent)) {
				result.push_back({ curDate, curEvent });
			}
		}

		/*
		copy_if(events.begin(), events.end(), back_inserter(result), [&](const string& event__) {
			return functor(curDate, event__);
		});
		*/


		/*
		vector<string> tempVector;
		tempVector.assign(events.begin(), events.end());

		auto endIter = stable_partition(tempVector.begin(), tempVector.end(),
			[&](const string& event__) {
				return functor(curDate, event__);
			});

		for (auto it = tempVector.begin(); it != endIter; it++) {
			result.push_back({ curDate, *it });
		}
		*/
	}
	return result;
}

DbPair Database::Last(const Date& date) const {

	auto greaterElemIter = dates.upper_bound(date);

	// if (greaterElemIter == dates.begin() || distance(dates.begin(), dates.end()) == 0) {
	if (greaterElemIter == dates.begin() || dates.empty()) {
		throw invalid_argument("Exception case");
	}
	else {
		Date lastDate = *(--greaterElemIter);
		return { lastDate, *(--dbVec.at(lastDate).end()) };
	}
}
