#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;

class ReadingManager {
    static const int MAX_USER_COUNT_ = 100'000;

    map<int, int> usersCurrentPosition;
    map<int, set<int>> pagesInfos;

public:
    ReadingManager() {}

    void Read(int user_id, int page_count) {

        // remove prev info
        if (usersCurrentPosition.count(user_id) != 0) {
            pagesInfos[usersCurrentPosition[user_id]].erase(user_id);

            if (pagesInfos[usersCurrentPosition[user_id]].empty()) {
                pagesInfos.erase(usersCurrentPosition[user_id]);
            }
        }

        pagesInfos[page_count].insert(user_id);
        usersCurrentPosition[user_id] = page_count;
    }

    double Cheer(int user_id) const {

        if (usersCurrentPosition.count(user_id) == 0) {
            return 0.;
        }

        if (usersCurrentPosition.size() == 1) {
            return 1.;
        }

        int currentUserPage = usersCurrentPosition.at(user_id);
        
        int usersBeforNb = 0;
        for (const auto& pageInfo : pagesInfos) {
            if (pageInfo.first < currentUserPage) {
                usersBeforNb += pageInfo.second.size();
            }
            else {
                break;
            }
        }

        return usersBeforNb * 1. / (usersCurrentPosition.size() - 1);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}