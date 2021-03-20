#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

// first part
/*
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {

    string curSym;
    curSym.push_back(prefix);

    auto startIt = std::lower_bound(range_begin, range_end, curSym, [](const string& sym, const string& curSym) {
        return sym < curSym;
    });

    curSym.clear();
    curSym.push_back(++prefix);

    auto endtIt = std::lower_bound(range_begin, range_end, curSym, [](const string& sym, const string& curSym) {
        return sym < curSym;
    });

    return std::make_pair(startIt, endtIt);
}

void autoTests() {

    vector<pair<vector<string>, vector<pair<char, pair<int, int>>>>> autoTests = { // vector

        // TEST #0
        { // pair
            { "moscow", "saint-petersburg", "samara", "vitebsk", "vladimir", "vologda", "vorkuta", "voronezh" }, // vector
            { // vector (subtets)
                {'a', {0,0}}, // pair
                {'b', {0,0}},
                {'c', {0,0}},
                {'d', {0,0}},
                {'c', {0,0}},
                {'m', {0,1}},
                {'n', {1,1}},
                {'o', {1,1}},
                {'p', {1,1}},
                {'s', {1,3}}, // er
                {'t', {3,3}},
                {'v', {3,8}}, // er
                {'z', {8,8}}
            }
        },

        // TEST #1
        {
            { "moscow", "murmansk", "vologda" },
            {
                {'p', {2,2}},
                {'z', {3,3}}
            }
        }
    };

    for (int testIdx = 0; testIdx < autoTests.size(); testIdx++) {
        vector<string> vecStr = autoTests[testIdx].first;
        vector<pair<char, pair<int, int>>> subtests = autoTests[testIdx].second;

        cout << "Test #" << testIdx + 1 << "/" << autoTests.size() << endl;

        for (int subtestIdx = 0; subtestIdx < subtests.size(); subtestIdx++) {

            cout << "\tSubtest #" << subtestIdx + 1 << "/" << subtests.size() << ": ";

            auto resultIters = FindStartsWith(begin(vecStr), end(vecStr), subtests[subtestIdx].first);
            pair<int, int> resultPair = { resultIters.first - begin(vecStr), resultIters.second - begin(vecStr) },
                           answer = subtests[subtestIdx].second;

            if (resultPair != answer) {
                cout << "error (" <<
                    "result: (" << resultPair.first << "," << resultPair.second << "), " <<
                    "answer: (" << answer.first << "," << answer.second << ")";
            }
            else {
                cout << "correct";
            }
            cout << endl;
        }
    }
}
*/

// second part
template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, string prefix) {

    string curSym = prefix;
    auto startIt = std::lower_bound(range_begin, range_end, curSym, [](const string& sym, const string& curSym) {
        return sym < curSym;
    });

    curSym.clear();
    curSym = prefix;

    curSym[curSym.length() - 1] = curSym[curSym.length() - 1] + 1;

    auto endtIt = std::lower_bound(range_begin, range_end, curSym, [](const string& sym, const string& curSym) {
        return sym < curSym;
    });

    return std::make_pair(startIt, endtIt);
}

void autoTests() {

    vector<pair<vector<string>, vector<pair<string, pair<int, int>>>>> autoTests = { // vector

        // TEST #0
        { // pair
            { "moscow", "saint-petersburg", "samara", "vitebsk", "vladimir", "vologda", "vorkuta", "voronezh" }, // vector
            { // vector (subtets)
                {"abc", {0,0}}, // pair
                {"bac", {0,0}},
                {"mos", {0,1}},
                {"moscow", {0,1}},
                {"n", {1,1}},
                {"o", {1,1}},
                {"p", {1,1}},
                {"s", {1,3}},
                {"t", {3,3}},
                {"v", {3,8}},
                {"z", {8,8}}
            }
        },

        // TEST #1
        {
            { "moscow", "motovilikha", "murmansk" },
            {
                {"mt", {2,2}},
                {"na", {3,3}}
            }
        }
    };

    for (int testIdx = 0; testIdx < autoTests.size(); testIdx++) {
        vector<string> vecStr = autoTests[testIdx].first;
        vector<pair<string, pair<int, int>>> subtests = autoTests[testIdx].second;

        cout << "Test #" << testIdx + 1 << "/" << autoTests.size() << endl;

        for (int subtestIdx = 0; subtestIdx < subtests.size(); subtestIdx++) {

            cout << "\tSubtest #" << subtestIdx + 1 << "/" << subtests.size() << ": ";

            auto resultIters = FindStartsWith(begin(vecStr), end(vecStr), subtests[subtestIdx].first);
            pair<int, int> resultPair = { resultIters.first - begin(vecStr), resultIters.second - begin(vecStr) },
                           answer = subtests[subtestIdx].second;

            if (resultPair != answer) {
                cout << "error (" <<
                    "result: (" << resultPair.first << "," << resultPair.second << "), " <<
                    "answer: (" << answer.first << "," << answer.second << ")";
            }
            else {
                cout << "correct";
            }
            cout << endl;
        }
    }
}

int main() {
    autoTests();

    return 0;
}