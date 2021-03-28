#pragma once
#include <map>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>

#include "date.h"
#include "node.h"

using namespace std;

using DbPair = pair<Date, string>;

ostream& operator<<(ostream& out, const DbPair& dbPair);

class Database {
	set<Date> dates;
	map<Date, vector<string>> dbVec;
	map<Date, set<string>> dbSet;

public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;
	int RemoveIf(function<bool(const Date& date_, const string& event_)> functor);
	vector<DbPair> FindIf(function<bool(const Date& date_, const string& event_)> functor) const;
	DbPair Last(const Date& date) const;
};