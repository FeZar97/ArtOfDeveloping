#include <set>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

set<int>::const_iterator FindNearestElement(const set<int>& numbers, int border) {

    /*
    auto lowerBound = numbers.lower_bound(border);
    auto upperBound = numbers.upper_bound(border);

    int numbersLength = distance(numbers.begin(), numbers.end());

    auto prevEl = upperBound;
    if (upperBound != numbers.begin()) {
        prevEl = prev(upperBound);
    }

    if (numbers.empty()) {
        return numbers.end();
    }

    // case when exist only 1 item and when exist prev elem
    if (lowerBound == upperBound) {

        // when exist prev elem need compare
        if (upperBound != numbers.begin() && upperBound != numbers.end() && distance(lowerBound, upperBound) == 0) {
            // return nearest
            if (abs((abs(*prevEl)) - abs(border)) <= abs(abs(*upperBound) - abs(border))) {
                return prevEl;
            }
            else {
                return upperBound;
            }
        }

        if (numbersLength && upperBound == numbers.end()) {
            return prevEl;
        }
        else {
            return upperBound;
        }
    }

    // if exist only lower elem
    if (upperBound == numbers.end()) {
        return lowerBound;
    }

// if exist both elements
    // if first is nearest
    if ( abs(abs(*lowerBound) - abs(border)) <= abs(abs(*upperBound) - abs(border)) ) {
        return lowerBound;
    }
    else {
        return upperBound;
    }
    */

    auto first_not_less = numbers.lower_bound(border);

    if (first_not_less == numbers.begin()) {
        return first_not_less;
    }

    auto last_less = prev(first_not_less);
    if (first_not_less == numbers.end()) {
        return last_less;
    }

    bool is_left = (border - *last_less <= *first_not_less - border);
    return is_left ? last_less : first_not_less;
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