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
        objects[0].push_back({ objectsCounter, move(object)});
        idToPriorityMap[objectsCounter] = 0;
        return objectsCounter++;
    }
    
    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
        IdOutputIt ids_begin) {

        uint64_t objectsCnt = 0;
        for (auto it = range_begin, it != range_end; it++) {
            *(ids_begin + objectsCnt++) = Add(*it);
        }
    }
    
    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        return idToPriorityMap.count(id);
    }
    
    // Получить объект по идентификатору
    const T& Get(Id id) const {
        Priority objPriority = idToPriorityMap[id];
        for (auto& obj : objects[objPriority]) {
            if (obj.first == id) {
                return obj;
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
            if ((*iter).first == id) {
                iterToPromote = iter;
                break;
            }
        }

        // move to next priority
        objects[nextPriority].push_back(move(*iterToPromote));

        // save changes in helpers-data
        idToPriorityMap[id] = nextPriority;

        // check that prev priority exist
        if (objects[objPriority].empty()) {
            objects.erase(objPriority);
        }
    }
    
    // Получить объект с максимальным приоритетом и его приоритет
    pair<const T&, int> GetMax() const;
    
    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<T, int> PopMax();

private:
    using Priority = uint64_t;

    template <typename T>
    using PriorityObject = pair<Id, T>;

    map<Priority, list<PriorityObject<T>>> objects;
    map<Id, Priority> idToPriorityMap;

    static uint64_t objectsCounter{ 0 };
};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable&) = delete;
    StringNonCopyable(StringNonCopyable&&) = default;
    StringNonCopyable& operator=(const StringNonCopyable&) = delete;
    StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
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
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
