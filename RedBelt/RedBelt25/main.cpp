#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;

class RoomBooking {
    string hotelName{ "" };
    int64_t reserveTime{ 0 };
    int64_t clientId{ 0 };
    unsigned int roomCount{ 0 };

public:
    RoomBooking() {}
    RoomBooking(const string& hotelName_, int64_t reserveTime_, int64_t clientId_, unsigned int roomCount_) {
        hotelName = hotelName_;
        reserveTime = reserveTime_;
        clientId = clientId_;
        roomCount = roomCount_;
    }

    bool operator<(const RoomBooking& rm) const {
        return reserveTime < rm.reserveTime;
    }

    bool operator==(const RoomBooking& rm) const {
        return reserveTime == rm.reserveTime;
    }

    bool operator>(const RoomBooking& rm) const {
        return reserveTime > rm.reserveTime;
    }

    int64_t getResrveTime() const {
        return reserveTime;
    }

    int64_t getClientId() const {
        return clientId;
    }

    int getRoomCount() const {
        return roomCount;
    }
};

class BookingManager {
    multiset<RoomBooking> reservs;
    map<string, multiset<RoomBooking>> hotelReserves;

public:
    BookingManager() {}

    void addReserve(const string& hotelName_, int64_t reserveTime_, int64_t clientId_, int roomCount_) {
        RoomBooking rb(hotelName_, reserveTime_, clientId_, roomCount_);
        reservs.insert(rb);
        hotelReserves[hotelName_].insert(rb);

        int64_t timeThreshold = (*reservs.rbegin()).getResrveTime() - 86400;
        auto firstCorrectIt = reservs.upper_bound(RoomBooking("", timeThreshold, 0, 0));

        reservs.erase(reservs.begin(), firstCorrectIt);
        for (auto& hotelPair : hotelReserves) {
            auto firstCorrectHotelIt = hotelPair.second.upper_bound(RoomBooking("", timeThreshold, 0, 0));
            hotelPair.second.erase(hotelPair.second.begin(), firstCorrectHotelIt);
        }
    }

    int getClients(const string& hotelName) const {
        if (hotelReserves.count(hotelName) == 0) {
            return 0;
        }

        const multiset<RoomBooking> &curHotelReserves = hotelReserves.at(hotelName);
        set<int64_t> uniqClients;

        int64_t timeThreshold = (*reservs.rbegin()).getResrveTime() - 86400;

        for (auto curIt = curHotelReserves.rbegin(); curIt != curHotelReserves.rend(); curIt++) {

            if ((*curIt).getResrveTime() <= timeThreshold) {
                break;
            }
            uniqClients.insert((*curIt).getClientId());
        }
        return uniqClients.size();
    }

    int getRooms(const string& hotelName) const {
        if (hotelReserves.count(hotelName) == 0) {
            return 0;
        }

        const multiset<RoomBooking> &curHotelReserves = hotelReserves.at(hotelName);
        int roomsCnt = 0;

        int64_t timeThreshold = (*reservs.rbegin()).getResrveTime() - 86400;

        for (auto curIt = curHotelReserves.rbegin(); curIt != curHotelReserves.rend(); curIt++) {

            if ((*curIt).getResrveTime() <= timeThreshold) {
                break;
            }
            roomsCnt += (*curIt).getRoomCount();
        }
        return roomsCnt;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingManager manager;

    int query_count;
    cin >> query_count;

    int64_t reserveTime, clientId;
    string queryType, hotelName;
    int roomCount;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        cin >> queryType;

        if (queryType == "BOOK") {
            cin >> reserveTime >> hotelName >> clientId >> roomCount;
            manager.addReserve(hotelName, reserveTime, clientId, roomCount);
        }
        else if (queryType == "CLIENTS") {
            cin >> hotelName;
            cout << manager.getClients(hotelName) << endl;
        }
        else if (queryType == "ROOMS") {
            cin >> hotelName;
            cout << manager.getRooms(hotelName) << endl;
        }
    }

    return 0;
}