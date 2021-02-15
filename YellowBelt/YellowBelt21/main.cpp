#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {

    string strType;
    int stopsCnt;
    is >> strType;

    if (strType == "NEW_BUS") {
        q.type = QueryType::NewBus;
        cin >> q.bus >> stopsCnt;

        q.stops.clear();
        q.stops.resize(stopsCnt);
        for (int i = 0; i < stopsCnt; i++) {
            cin >> q.stops[i];
        }
    }
    else if (strType == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    }
    else if (strType == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    }
    else if (strType == "ALL_BUSES") {
        q.type = QueryType::AllBuses;
    }

    return is;
}

using BusesStopsMap = map<string, vector<string>>;

// ------ BusesForStopResponse ------
struct BusesForStopResponse {
    vector<string> busesForStop;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.busesForStop.empty()) {
        os << "No stop" << endl;
    }
    else {
        for (const auto& bus : r.busesForStop) {
            os << bus << " ";
        }
        cout << endl;
    }
    return os;
}

// ------ StopsForBusResponse ------
struct StopsForBusResponse {
    vector<string> stops;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops.size() == 0) {
        os << "No bus" << endl;
    }
    else {
        for (const auto& stopInfo : r.stops) {
            os << stopInfo << endl;
        }
    }
    return os;
}

// ------ AllBusesResponse ------
struct AllBusesResponse {
    vector<string> bussesInfo;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {

    if (r.bussesInfo.empty()) {
        os << "No buses" << endl;
    }
    else {
        for (const auto& busInfo : r.bussesInfo) {
            os << busInfo << endl;
        }
    }
    return os;
}

// ------ BusManager ------
class BusManager {
    BusesStopsMap busesToStop;
    BusesStopsMap stopsToBus;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        stopsToBus[bus] = stops;

        for (const auto& stop : stops) {
            busesToStop[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse result;
        if (busesToStop.count(stop)) {
            for (const auto& bus : busesToStop.at(stop)) {
                result.busesForStop.push_back(bus);
            }
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {

        StopsForBusResponse result;

        vector<string> stopsInfo;
        if (stopsToBus.count(bus)) {
            for (const string& stop : stopsToBus.at(bus)) {
                string stopInfo = "Stop " + stop + ": ";
                if (busesToStop.at(stop).size() == 1) {
                    stopInfo += "no interchange";
                }
                else {
                    for (const string& otherBus : busesToStop.at(stop)) {
                        if (bus != otherBus) {
                            stopInfo += otherBus + " ";
                        }
                    }
                }
                stopsInfo.push_back(stopInfo);
            }
        }
        result.stops = stopsInfo;
        return result;
    }

    AllBusesResponse GetAllBuses() const {

        AllBusesResponse result;

        if (stopsToBus.size()) {
            for (const auto& busInfo :stopsToBus) {

                string busFullInfo = "Bus " + busInfo.first + ": ";
                for (const string& stop : busInfo.second) {
                    busFullInfo += stop + " ";
                }
                result.bussesInfo.push_back(busFullInfo);
            }
        }

        return result;
    }
};

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}