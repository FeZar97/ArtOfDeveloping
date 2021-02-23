#include "query.h"

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