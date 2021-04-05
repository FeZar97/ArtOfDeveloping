#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <set>
#include <utility>

// #include "../test_runner.h"

using namespace std;

class RoomBooking {
    string hotelName{ "" };
    int64_t reserveTime{ 0 };
    int64_t clientId{ 0 };
    unsigned int roomCount{ 0 };

public:
    RoomBooking() {}
    RoomBooking(int64_t reserveTime_, const string& hotelName_, int64_t clientId_, unsigned int roomCount_) {
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

    bool operator<=(const RoomBooking& rm) const {
        return (*this < rm) || (*this == rm);
    }

    string getHotelName() const {
        return hotelName;
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

class HotelManager {
    deque<RoomBooking> reservs;
    map<string, uint64_t> hotelRoomsReserves;
    // _clients[hotel_name][client_id] += room_count;
    // _rooms[hotel_name] += room_count;

    auto dequeBinarySearchPos(const deque<RoomBooking> &reservs, const RoomBooking& elem) {
        auto beginIt = reservs.begin(),
            endIt = reservs.end(),
            middleIt = reservs.begin();
        uint64_t curLength = distance(reservs.begin(), reservs.end());

        while (curLength) {
            curLength = distance(beginIt, endIt) / 2;
            middleIt = beginIt + curLength;

            if (*middleIt > elem) {
                endIt = middleIt;
            }
            else if (*middleIt <= elem) {
                beginIt = middleIt;
            }
        }
        return endIt;
    }

    void removeOldReserves(deque<RoomBooking> &reserves, const RoomBooking& elem) {
        RoomBooking removeThreshold(elem.getResrveTime() - 86400, "", 0, 0);
        auto thresholdIt = dequeBinarySearchPos(reserves, removeThreshold);
        reserves.erase(reserves.begin(), thresholdIt);
    }

public:
    HotelManager() {}

    void addReserve(RoomBooking rb) {
        addReserve(rb.getResrveTime(), rb.getHotelName(), rb.getClientId(), rb.getRoomCount());
    }

    void addReserve(int64_t reserveTime_, const string& hotelName_, int64_t clientId_, int roomCount_) {
        RoomBooking rb(reserveTime_, hotelName_, clientId_, roomCount_);

        // insert into reservs
        if (!reservs.empty()) {
            auto bestInsertIt = dequeBinarySearchPos(reservs, rb);
            reservs.insert(bestInsertIt, rb);
            removeOldReserves(reservs, rb);
        }
        else {
            reservs.push_back(rb);
        }
    }

    int getClients(const string& hotelName) const {
        if (hotelReserves.count(hotelName) == 0) {
            return 0;
        }

        const deque<RoomBooking> &curHotelReserves = hotelReserves.at(hotelName);
        set<int64_t> uniqClients;

        for (auto curIt = curHotelReserves.begin(); curIt != curHotelReserves.end(); curIt++) {
            uniqClients.insert((*curIt).getClientId());
        }
        return uniqClients.size();
    }

    int getRooms(const string& hotelName) const {
        if (hotelReserves.count(hotelName) == 0) {
            return 0;
        }

        const deque<RoomBooking> &curHotelReserves = hotelReserves.at(hotelName);
        int roomsCnt = 0;

        for (auto curIt = curHotelReserves.begin(); curIt != curHotelReserves.end(); curIt++) {
            roomsCnt += (*curIt).getRoomCount();
        }
        return roomsCnt;
    }
};

/*
void Test1() {
    HotelManager hm;
    ASSERT_EQUAL(hm.getClients("M"), 0);
    ASSERT_EQUAL(hm.getRooms("M"), 0);
    hm.addReserve({ 10,"F",1,2 });
    hm.addReserve({ 10,"M",1,1 });
    hm.addReserve({ 86409,"F",2,1 });
    ASSERT_EQUAL(hm.getClients("F"), 2);
    ASSERT_EQUAL(hm.getRooms("F"), 3);
    ASSERT_EQUAL(hm.getClients("M"), 1);
    hm.addReserve({ 86410,"M",2,10 });
    ASSERT_EQUAL(hm.getRooms("F"), 1);
    ASSERT_EQUAL(hm.getRooms("M"), 10);
}
void Test2() {
    HotelManager hm;

    ASSERT_EQUAL(hm.getRooms("a"), 0);
    ASSERT_EQUAL(hm.getClients("a"), 0);
    hm.addReserve({ -100000, "a", 100000, 1000 });
    hm.addReserve({ -100000, "a", 100003, 1000 });
    hm.addReserve({ -100000, "b", 100002, 1000 });
    ASSERT_EQUAL(hm.getRooms("a"), 2000);
    ASSERT_EQUAL(hm.getClients("a"), 2);
    hm.addReserve({ -10000, "a", 100002, 1000 });
    ASSERT_EQUAL(hm.getRooms("a"), 1000);
    ASSERT_EQUAL(hm.getClients("a"), 1);
    ASSERT_EQUAL(hm.getRooms("b"), 0);
    ASSERT_EQUAL(hm.getClients("b"), 0);
}
void Test3() {
    HotelManager manager;

    // Test empty bookings
    ASSERT_EQUAL(manager.getClients("mariott"), 0);
    ASSERT_EQUAL(manager.getRooms("mariott"), 0);

    manager.addReserve({ 0, "mariott", 1, 10 });
    manager.addReserve({ 0, "mariott", 2, 1 });
    manager.addReserve({ 0, "mariott", 3, 1 });
    manager.addReserve({ 0, "mariott", 4, 1 });
    manager.addReserve({ 0, "hilton", 1, 1 });
    manager.addReserve({ 1, "hilton", 2, 1 });

    // Test correctness
    ASSERT_EQUAL(manager.getClients("mariott"), 4);
    ASSERT_EQUAL(manager.getRooms("mariott"), 13);
    ASSERT_EQUAL(manager.getClients("hilton"), 2);
    ASSERT_EQUAL(manager.getRooms("hilton"), 2);

    // Test event past 1 day resets statics
    manager.addReserve({ 86400, "mariott", 1, 1 });
    ASSERT_EQUAL(manager.getClients("mariott"), 1);
    ASSERT_EQUAL(manager.getRooms("mariott"), 1);
    ASSERT_EQUAL(manager.getClients("hilton"), 1);
    ASSERT_EQUAL(manager.getRooms("hilton"), 1);

    // Test no clients and room for the last day
    manager.addReserve({ 86401, "mariott", 5, 1 });
    ASSERT_EQUAL(manager.getClients("mariott"), 2);
    ASSERT_EQUAL(manager.getRooms("mariott"), 2);
    ASSERT_EQUAL(manager.getClients("hilton"), 0);
    ASSERT_EQUAL(manager.getRooms("hilton"), 0);
}
void Test4() {
    HotelManager b;

    ASSERT_EQUAL(b.getRooms("a"), 0);
    ASSERT_EQUAL(b.getClients("a"), 0);

    ASSERT_EQUAL(b.getRooms("b"), 0);
    ASSERT_EQUAL(b.getClients("c"), 0);

    b.addReserve({ -100000,"a",100000,1000 });
    b.addReserve({ -100000,"a",100003,1000 });
    b.addReserve({ -100000,"b",100002,1000 });
    ASSERT_EQUAL(b.getRooms("a"), 2000);
    ASSERT_EQUAL(b.getClients("a"), 2);

    b.addReserve({ -10000,"a",100002,1000 });
    ASSERT_EQUAL(b.getRooms("a"), 1000);
    ASSERT_EQUAL(b.getClients("a"), 1);
    ASSERT_EQUAL(b.getRooms("b"), 0);
    ASSERT_EQUAL(b.getClients("b"), 0);
}
void Test5() {
    HotelManager b;

    b.addReserve({ 0, "a", 0, 1 });
    b.addReserve({ 1, "a", 1, 2 });
    b.addReserve({ 86400, "a", 1, 3 });
    ASSERT_EQUAL(b.getClients("a"), 1);
    ASSERT_EQUAL(b.getRooms("a"), 5);
}
void Test6() {
    HotelManager b;

    b.addReserve({ -86400, "a", 2, 2 });
    b.addReserve({ 0, "a", 1, 5 });
    ASSERT_EQUAL(b.getClients("a"), 1);
    ASSERT_EQUAL(b.getRooms("a"), 5);
}
void Test7() {
    HotelManager b;

    b.addReserve({ 1, "a", 11, 4 });
    b.addReserve({ 50000, "a", 11, 5 });
    b.addReserve({ 90000, "a", 22, 2 });
    ASSERT_EQUAL(b.getClients("a"), 2);
    ASSERT_EQUAL(b.getRooms("a"), 7);
}
void Test8() {
    HotelManager b;

    b.addReserve({ 2147483647, "a", 1, 3 });
    b.addReserve({ 2147483648, "a", 2, 11 });
    b.addReserve({ 4147483648, "a", 3, 13 });
    ASSERT_EQUAL(b.getClients("a"), 1);
    ASSERT_EQUAL(b.getRooms("a"), 13);
}

void AllTests() {
    TestRunner tr;
    RUN_TEST(tr, Test1);
    RUN_TEST(tr, Test2);
    RUN_TEST(tr, Test3);
    RUN_TEST(tr, Test4);
    RUN_TEST(tr, Test5);
    RUN_TEST(tr, Test6);
    RUN_TEST(tr, Test7);
    RUN_TEST(tr, Test8);
}
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    HotelManager manager;

    int query_count;
    cin >> query_count;

    int64_t reserveTime, clientId;
    string queryType, hotelName;
    int roomCount;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        cin >> queryType;

        if (queryType == "BOOK") {
            cin >> reserveTime >> hotelName >> clientId >> roomCount;
            manager.addReserve(reserveTime, hotelName, clientId, roomCount);
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