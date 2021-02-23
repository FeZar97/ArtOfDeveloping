#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    stopsToBus[bus] = stops;

    for (const auto& stop : stops) {
        busesToStop[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
    BusesForStopResponse result;
    if (busesToStop.count(stop)) {
        for (const auto& bus : busesToStop.at(stop)) {
            result.busesForStop.push_back(bus);
        }
    }
    return result;
}

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {

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

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse result;

    if (stopsToBus.size()) {
        for (const auto& busInfo : stopsToBus) {

            string busFullInfo = "Bus " + busInfo.first + ": ";
            for (const string& stop : busInfo.second) {
                busFullInfo += stop + " ";
            }
            result.bussesInfo.push_back(busFullInfo);
        }
    }

    return result;
}
