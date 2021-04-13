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
        uint32_t curStepNb = 1;
        if (curIterPos == prev(prevItersOrder.end())) {
            curIterPos = prevItersOrder.begin();
        }
        else {
            advance(curIterPos, 1);
        }

        // remove previous iter
        prevItersOrder.erase(iterToRemove);
        curRangeLength--;

        while (curStepNb < step_size) {

            curStepNb++;

            // check, that curIterPos not point to end()
            if (curIterPos == prev(prevItersOrder.end())) {
                curIterPos = prevItersOrder.begin();
                continue;
            }

            advance(curIterPos, 1);
        }
    }

    // now size of prevItersOrder == 1, need move last value from prevItersOrder into back of resultElemOrder
    resultElemOrder.push_back(move(*(prevItersOrder.back())));

    // return values to home
    move(resultElemOrder.begin(), resultElemOrder.end(), first);
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

void TestStep1() {
    vector<char> chars{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' };
    MakeJosephusPermutation(begin(chars), end(chars), 1);
    ASSERT_EQUAL(chars, vector<char>({ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' }));
}

void TestStep2() {
    vector<char> chars{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' };
    MakeJosephusPermutation(begin(chars), end(chars), 2);
    ASSERT_EQUAL(chars, vector<char>({ 'a', 'c', 'e', 'g', 'i', 'k', 'b', 'f', 'j', 'd', 'l', 'h' }));
}

void TestStep3() {
    vector<char> chars{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' };
    MakeJosephusPermutation(begin(chars), end(chars), 3);
    ASSERT_EQUAL(chars, vector<char>({ 'a', 'd', 'g', 'j', 'b', 'f', 'k', 'e', 'l', 'i', 'c', 'h' }));
}

void TestStep4() {
    vector<char> chars{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' };
    MakeJosephusPermutation(begin(chars), end(chars), 4);
    ASSERT_EQUAL(chars, vector<char>({ 'a', 'e', 'i', 'b', 'g', 'l', 'h', 'd', 'c', 'f', 'k', 'j' }));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    
    RUN_TEST(tr, TestStep1);
    RUN_TEST(tr, TestStep2);
    RUN_TEST(tr, TestStep3);
    RUN_TEST(tr, TestStep4);

    return 0;
}
