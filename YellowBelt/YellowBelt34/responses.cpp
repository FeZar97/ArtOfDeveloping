#include "responses.h"

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