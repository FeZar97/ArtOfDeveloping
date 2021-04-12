#include <cstdint>
#include <iterator>
#include <numeric>
#include <list>
#include <iostream>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    list<RandomIt> prevItersOrder;
    list<typename RandomIt::value_type> resultElemOrder;

    for (auto it = first; it != last; it++) {
        prevItersOrder.push_back(it);
    }

    typename list<RandomIt>::iterator curIterPos = prevItersOrder.begin(),
                                      iterToRemove;

    uint32_t curRangeLength = prevItersOrder.size();

    while (curRangeLength > 1) {

        // save iter to remove
        iterToRemove = curIterPos;

        // move next value from source to temp vector
        resultElemOrder.push_back(move(*(*curIterPos)));

        // shift curIterPos
        uint32_t curStepNb = 0,
                 nextStepSize = step_size % curRangeLength;

        // shift curIterPos on 1, because now it point on self
        if (nextStepSize == 0) {
            nextStepSize = 1;
        }

        while (curStepNb < nextStepSize) {

            // uint32_t distanceToEnd = distance(curIterPos, prevItersOrder.end());
            uint32_t distanceToEnd = 1;
            uint32_t availableShift = min(distanceToEnd, nextStepSize - curStepNb);

            advance(curIterPos, availableShift);
            curStepNb += availableShift;

            // check, that curIterPos not point to end()
            if (curIterPos == prevItersOrder.end()) {
                curIterPos = prevItersOrder.begin();
            }
        }

        // remove previous iter
        prevItersOrder.erase(iterToRemove);
        curRangeLength--;
    }

    // now size of prevItersOrder == 1, need move last value from prevItersOrder into back of resultElemOrder
    resultElemOrder.push_back(move(*(prevItersOrder.back())));

    // return values to home
    auto sourceIt = resultElemOrder.begin();
    for (RandomIt destIt = first; destIt != last; destIt++) {
        *destIt = move(*sourceIt++);
    }
}
