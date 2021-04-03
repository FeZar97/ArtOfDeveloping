#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

// #include "../test_runner.h"

using namespace std;

class RouteManager {

    map<int, set<int>> reachable_lists_;

public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }

    int FindNearestFinish(int start, int finish) const {
        int maxRange = abs(finish - start);
        if (reachable_lists_.count(start) < 1) {
            return maxRange;
        }
        const set<int>& reachable_stations = reachable_lists_.at(start);
        const auto finish_pos = reachable_stations.lower_bound(finish);
        if (finish_pos != end(reachable_stations)) {
            maxRange = min(maxRange, abs(finish - *finish_pos));
        }
        if (finish_pos != begin(reachable_stations)) {
            maxRange = min(maxRange, abs(finish - *prev(finish_pos)));
        }
        return maxRange;
    }
};

/*
void Test1() {
    RouteManager routes;

    istringstream is("7\nADD -2 5\nADD 10 4\nADD 5 8\nGO 4 10\nGO 4 -2\nGO 5 0\nGO 5 100\na");

    ostringstream os;

    int query_count;
    is >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        is >> query_type;
        int start, finish;
        is >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO") {
            os << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    ASSERT_EQUAL(os.str(), "0\n6\n2\n92\n");
}
*/

int main() {

    RouteManager routes;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int start, finish;
        cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO") {
            cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}