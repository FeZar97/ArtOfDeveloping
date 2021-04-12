#include <cstdint>
#include <iterator>
#include <numeric>
#include <list>
#include <iostream>

#include "../test_runner.h"

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

vector<int> MakeTestVector() {
    vector<int> numbers(10);
    iota(begin(numbers), end(numbers), 0);
    return numbers;
}

void TestIntVector() {
    const vector<int> numbers = MakeTestVector();
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
        ASSERT_EQUAL(numbers_copy, numbers);
    }
    {
        vector<int> numbers_copy = numbers;
        MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
        ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
    }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»
struct NoncopyableInt {
    int value;
    
    NoncopyableInt(int value) : value(value) {}
    
    NoncopyableInt(const NoncopyableInt&) = delete;
    NoncopyableInt& operator=(const NoncopyableInt&) = delete;
    
    NoncopyableInt(NoncopyableInt&&) = default;
    NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
    return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
    return os << v.value;
}

void TestAvoidsCopying() {
    vector<NoncopyableInt> numbers;
    numbers.push_back({1});
    numbers.push_back({2});
    numbers.push_back({3});
    numbers.push_back({4});
    numbers.push_back({5});
    
    MakeJosephusPermutation(begin(numbers), end(numbers), 2);
    
    vector<NoncopyableInt> expected;
    expected.push_back({1});
    expected.push_back({3});
    expected.push_back({5});
    expected.push_back({4});
    expected.push_back({2});
    
    ASSERT_EQUAL(numbers, expected);
}

void TestMeaning() {
    vector<char> chars{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' };
    MakeJosephusPermutation(begin(chars), end(chars), 3);

    ASSERT_EQUAL(chars, vector<char>({ 'a', 'd', 'g', 'j', 'b', 'f', 'k', 'e', 'l', 'i', 'c', 'h' }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    RUN_TEST(tr, TestMeaning);
    return 0;
}
