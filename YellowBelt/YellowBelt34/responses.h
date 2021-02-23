#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

using BusesStopsMap = map<string, vector<string>>;

// ------ BusesForStopResponse ------
struct BusesForStopResponse {
    vector<string> busesForStop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

// ------ StopsForBusResponse ------
struct StopsForBusResponse {
    vector<string> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r);

// ------ AllBusesResponse ------
struct AllBusesResponse {
    vector<string> bussesInfo;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);
