#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <map>
#include <list>
#include <utility>
#include <vector>

#include "../test_runner.h"

using namespace std;

template <typename T>
class PriorityCollection {

public:
    using Id = uint64_t;
    
    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(T object) {
        objects[0].push_back({ move(object), objectsCounter });
        idToPriorityMap[objectsCounter] = 0;
        return objectsCounter++;
    }
    
    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
        IdOutputIt ids_begin) {

        for (auto it = range_begin; it != range_end; it++) {
            *ids_begin = Add(move(*it));
            ids_begin++;
        }
    }
    
    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return idToPriorityMap.count(id);
    }
    
    // Получить объект по идентификатору
    const T& Get(Id id) const {
        const Priority &objPriority = idToPriorityMap.at(id);
        for (const PriorityObject<T> &obj : objects.at(objPriority)) {
            if (obj.second == id) {
                return obj.first;
            }
        }
    }
    
    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        Priority objPriority = idToPriorityMap[id];
        Priority nextPriority = objPriority + 1;

        auto iterToPromote = objects[objPriority].begin();

        // find object to promote
        for (auto iter = objects[objPriority].begin(); iter != objects[objPriority].end(); iter++) {
            if ((*iter).second == id) {
                iterToPromote = iter;
                break;
            }
        }

        // move to next priority
        objects[nextPriority].push_back(move(*iterToPromote));

        // remove prev
        objects[objPriority].erase(iterToPromote);


        // save changes in helpers-data
        idToPriorityMap[id] = nextPriority;

        // check that prev priority exist
        // if not - remove key
        if (objects[objPriority].empty()) {
            objects.erase(objPriority);
        }

        if (nextPriority > maxPriority) {
            maxPriority = nextPriority;
        }
    }
    
    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const {
        return { objects.at(maxPriority).back().first, maxPriority };
    }
    
    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax() {

        // find iter with max Id
        auto maxIter = objects[maxPriority].begin();
        for (auto iter = objects[maxPriority].begin(); iter != objects[maxPriority].end(); iter++) {
            if ((*iter).second > (*maxIter).second) {
                maxIter = iter;
            }
        }

        pair<T, int> result = make_pair<T, int>(move((*maxIter).first), static_cast<int>(maxPriority));

        // remove from idToPriority map
        idToPriorityMap.erase((*maxIter).second);

        // remove maxIter
        objects[maxPriority].erase(maxIter);

        if (objects[maxPriority].empty()) {
            objects.erase(maxPriority);
        }

        maxPriority = 0;
        if (objects.size()) {
            maxPriority = (*prev(objects.end())).first;
        }

        return result;
    }

private:
    using Priority = int;

    template <typename SomeType>
    using PriorityObject = pair<SomeType, Id>;

    Priority maxPriority{ 0 };
    map<Priority, list<PriorityObject<T>>> objects;
    map<Id, Priority> idToPriorityMap;

    uint64_t objectsCounter{ 0 };
};

class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy1() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");
    
    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
}

void TestNoCopy2() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);

    strings.PopMax();

    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
}

void TestNoCopy3() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);

    strings.PopMax();
    strings.PopMax();

    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
}

void TestNoCopy4() {
    PriorityCollection<StringNonCopyable> strings;

    vector<StringNonCopyable> testVector;
    testVector.push_back("white");
    testVector.push_back("yellow");
    testVector.push_back("red");

    vector<PriorityCollection<StringNonCopyable>::Id> resultId(3),
        expected{0, 1 ,2};

    strings.Add(testVector.begin(), testVector.end(), resultId.begin());

    ASSERT_EQUAL(resultId, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy1);
    RUN_TEST(tr, TestNoCopy2);
    RUN_TEST(tr, TestNoCopy3);
    RUN_TEST(tr, TestNoCopy4);
    return 0;
}
