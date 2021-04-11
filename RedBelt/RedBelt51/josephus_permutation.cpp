#include <cstdint>
#include <iterator>
#include <numeric>
#include <list>
#include <iostream>

#include "../test_runner.h"

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
    //              0 1 2 3 4 5 6 7 8 9 0 1
    // prev order: 'a b c d e f g h i j k l', new order: ''
    // prev order: 'X b c d e f g h i j k l', new order: 'a'
    // prev order: 'X b c X e f g h i j k l', new order: 'a d'
    // prev order: 'X b c X e f X h i j k l', new order: 'a d g'
    // prev order: 'X b c X e f X h i X k l', new order: 'a d g j'
    // prev order: 'X X c X e f X h i X k l', new order: 'a d g j b'
    // prev order: 'X X c X e X X h i X k l', new order: 'a d g j b f'
    // prev order: 'X X c X e X X h i X X l', new order: 'a d g j b f k'
    // prev order: 'X X c X X X X h i X X l', new order: 'a d g j b f k e'
    // prev order: 'X X c X X X X h i X X X', new order: 'a d g j b f k e l'
    // prev order: 'X X c X X X X h X X X X', new order: 'a d g j b f k e l i'
    // prev order: 'X X X X X X X h X X X X', new order: 'a d g j b f k e l i c'
    // prev order: 'X X X X X X X X X X X X', new order: 'a d g j b f k e l i c h'


    //               0 1 2 3 4 5 6 7 8 9 10 11         STEP =3
    // prev order: '\a b c d e f g h i j k l', size = 12, new order: '', curIterPos = 'a'
    // prev order: 'b c \d e f g h i j k l', size = 11, new order: 'a',  curIterPos = 'd', iterToRemove 'a'
    // prev order: 'b c e f \g h i j k l', size = 10, new order: 'a d',  curIterPos = 'g', iterToRemove 'd'
    // prev order: 'b c e f h i \j k l', size = 9, new order: 'a d g',   curIterPos = 'j', iterToRemove 'g'
    // prev order: '\b c e f h i k l', size = 8, new order: 'a d g j',   curIterPos = 'b', iterToRemove 'j'
    // prev order: 'c e \f h i k l', size = 7, new order: 'a d g j b',   curIterPos = 'f', iterToRemove 'b'
    // prev order: 'c e h i \k l', size = 6, new order: 'a d g j b f',   curIterPos = 'k', iterToRemove 'f'
    // prev order: 'c \e h i l', size = 5, new order: 'a d g j b f k',   curIterPos = 'e', iterToRemove 'k'
    // prev order: 'c h i \l', size = 4, new order: 'a d g j b f k e',   curIterPos = 'l', iterToRemove 'e'
    // prev order: 'c h \i', size = 3, new order: 'a d g j b f k e l',   curIterPos = 'i', iterToRemove 'l'
    // prev order: '\c h', size = 2, new order: 'a d g j b f k e l i',   curIterPos = 'c', iterToRemove 'i'
    // prev order: '\h', size = 1, new order: 'a d g j b f k e l i c',   curIterPos = 'h', iterToRemove 'c'
    //                             new order: '0 3 6 9 1 5 10 4 11 8 2

    list<RandomIt> prevItersOrder, 
                   newItersOrder;

    for (auto it = first; it != last; it++) {
        prevItersOrder.push_back(first);
    }

    list<RandomIt>::iterator curIterPos = prevItersOrder.begin(),
                             iterToRemove;
    
    while (prevItersOrder.size() > 1) {
        iterToRemove = curIterPos;
        newItersOrder.push_back(*curIterPos);

        size_t distToEnd = distance(curIterPos, prevItersOrder.end());

        prevItersOrder.erase(iterToRemove);

        // prev order: 'a b c d e f g \h i j k l'
        // new order:  'a b c d e f g \i j k l'
        // step 5
        // distToEnd = 5
        if (distToEnd == step_size) {
            curIterPos = prevItersOrder.begin();
        }
        // prev order: 'a b c d e \f g h i j k l'
        // new order:  'a b c d e \g h i j k l'
        // step 5
        // distToEnd = 7
        else if (distToEnd > step_size) {
            curIterPos += step_size;
        }
        // if distToEnd < step_size
        // prev order: 'a b c d e f g h i j \k l'
        // new order:  'a b c d e f g h i j \l'
        // step 5
        // distToEnd = 2
        else {
            curIterPos += step_size;
        }


    }

    // now size of prevItersOrder == 1
    // need insert last iter from prevItersOrder in back of newItersOrder
    newItersOrder.push_back()
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
    /*
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
*/
}

void TestMeaning() {
    vector<char> chars{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l' };

    MakeJosephusPermutation(begin(chars), end(chars), 3);

    cout << chars;
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    RUN_TEST(tr, TestAvoidsCopying);
    RUN_TEST(tr, TestMeaning);
    return 0;
}
