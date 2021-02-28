#include <set>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {

    auto equalRange = numbers.equal_range(border);

    // empty case and case, when exist only 1 item
    if (equalRange.first == equalRange.second) {
        return prev(end(numbers));
    }

    // if exist only lower elem
    if (equalRange.second == end(numbers)) {
        return equalRange.first;
    }

    // if exist both elements

    // if first is nearest
    if ( (abs(*equalRange.first) - abs(border)) <= (abs(*equalRange.second) - abs(border)) ) {
        return equalRange.first;
    }
    else {
        return equalRange.second;
    }
}

int main() {
    set<int> numbers = { 1, 4, 6 };

    // 1 4 4 6 6
    cout <<
        *FindNearestElement(numbers, 0) << " " <<
        *FindNearestElement(numbers, 3) << " " <<
        *FindNearestElement(numbers, 5) << " " <<
        *FindNearestElement(numbers, 6) << " " <<
        *FindNearestElement(numbers, 100) << endl;

    set<int> empty_set;

    // 1
    cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
    return 0;
}