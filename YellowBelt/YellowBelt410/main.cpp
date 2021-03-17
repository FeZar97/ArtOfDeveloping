#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {

    int rangeLength;
    pair<RandomIt, RandomIt> curPair{ range_begin, range_end };
    pair<RandomIt, RandomIt> resPair{ curPair };

    vector<string> inputList; // temp

    /*
    if (rangeLength == 1) {
        if ((*range_begin)[0] < prefix) {
            return { range_end , range_end };
        }
        else {
            return { range_begin , range_end };
        }
    }
    */

    do {
        resPair = curPair;

        // ---- temp -----
        inputList.clear();
        for (auto ptr = resPair.first; ptr != resPair.second; ptr++) {
            inputList.push_back(*ptr);
        }
        // ---- temp -----

        rangeLength = distance(curPair.first, curPair.second);

        if (rangeLength == 0) {
            return curPair;
        }

        // correct left board
        if ((*(curPair.first))[0] < prefix) {
            curPair.first += rangeLength / 2;
        }
        
        // correct right board
        if (rangeLength < 2) {
            rangeLength = 2;
        }
        if ((*(curPair.second - rangeLength / 2))[0] > prefix) {
            curPair.second -= rangeLength / 2;
        }
    } while (curPair != resPair && 
            curPair.second > curPair.first);


    if (distance(curPair.first, curPair.second) == 0) {
        return { curPair.first , curPair.first };
    }

    return { curPair.first , curPair.second };

    /*
    pair<bool, bool> areBordersEqualPrefix{false, false};
    while ( (!areBordersEqualPrefix.first || !areBordersEqualPrefix.second) &&
            range_begin != range_end &&
            rangeLength > 1) {

        rangeLength = distance(range_begin, range_end);

        int curShift = rangeLength / 2;

        // correct left board
        if( (*(range_begin + curShift))[0] < prefix ) {
            range_begin += curShift;
        }
        else if( (*(range_begin + curShift))[0] == prefix ) {
            areBordersEqualPrefix.first = true;
        }

        // correct right board
        if ((*(range_end - curShift))[0] > prefix) {
            range_end -= curShift;
        }
        else if ((*(range_end - curShift))[0] == prefix) {
            areBordersEqualPrefix.second = true;
        }
    }

    if (distance(range_begin, range_end) == 0) {
        return { range_begin , range_begin };
    }

    return { range_begin , range_end };
    */
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

int main() {
    autoTests();

    return 0;
}