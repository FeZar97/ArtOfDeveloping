#pragma once
#include <map>
#include <vector>
#include <set>
#include <iomanip>

#include "date.h"
#include "node.h"

using namespace std;

class Database {
	map<Date, vector<string>> dbVec;
	map<Date, set<string>> dbSet;

public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	int RemoveIf(bool *functor(const Date& date, const string& event));
	vector<string> FindIf(bool* func());
	string Last(const Date& date);

	bool DeleteEvent(const Date& date, const string& event);
	int DeleteDate(const Date& date);
	vector<string> Find(const Date& date) const;
};

