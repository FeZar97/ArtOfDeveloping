#include <tuple>
#include <vector>
#include <string>
#include <iostream>

using namespace std;


template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {

    int rangeLength = distance(range_begin, range_end);

    if (rangeLength == 0) {
        return { range_begin , range_end };
    }

    if (rangeLength == 1) {
        if ((*range_begin)[0] < prefix) {
            return { range_end , range_end };
        }
        else {
            return { range_begin , range_end };
        }
    }

    while (rangeLength > 2) {
        rangeLength = distance(range_begin, range_end);

        // correct left board
        if( (*(range_begin + rangeLength/2))[0] < prefix ) {
            range_begin += rangeLength / 2;
        }

        // correct right board
        if ((*(range_end - rangeLength / 2))[0] > prefix) {
            range_end -= rangeLength / 2;
        }
    }

    return { range_begin , range_end };
}

int main() {

    /*
    const vector<string> sorted_strings2 = { "moscow", "saint-petersburg", "samara", "vitebsk", "vladimir", "vologda", "vorkuta", "voronezh" }; // 8
    // const vector<string> sorted_strings2 = { "moscow", "saint-petersburg", "samara", "vitebsk" }; // 4
    // const vector<string> sorted_strings2 = { "moscow", "saint-petersburg" }; // 2
    const auto m_result1 =
        FindStartsWith(begin(sorted_strings2), end(sorted_strings2), 'm');
    for (auto it = m_result1.first; it != m_result1.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // const vector<string> sorted_strings1 = { "abakan", "kaliningrad", "novosibirsk", "new-york", "moscow", "murmansk", "vologda" }; // 7
    */

    const vector<string> sorted_strings = { "moscow", "murmansk", "vologda" };

    const auto m_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
    for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl; // moscow murmansk

    const auto p_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
    cout << (p_result.first - begin(sorted_strings)) << " " <<
        (p_result.second - begin(sorted_strings)) << endl; // 2 2 

    const auto z_result =
        FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
    cout << (z_result.first - begin(sorted_strings)) << " " <<
        (z_result.second - begin(sorted_strings)) << endl; // 3 3

    return 0;
}