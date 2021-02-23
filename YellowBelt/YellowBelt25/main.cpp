#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

/*
bool IsPalindrom(const string& str) {
}
*/

/*
ѕри этом учитывайте, что правильна€ реализаци€ функции:
    * считает пустую строку палиндромом;
    * считает строку из одного символа палиндромом;
    * осуществл€ет обычное сравнение символов на равенство, не игнориру€ никакие символы, в том числе пробельные.

ѕримеры ошибок:
    * игнорируетс€ первый или последний символ;
    * сравнение соответствующих символов завершаетс€ не в середине строки, а раньше;
    * игнорируютс€ пробелы
*/

void Test1() {
    AssertEqual(IsPalindrom(""), 1, "Test1");
}

void Test2() {
    AssertEqual(IsPalindrom("1"), 1, "Test2");
}

void Test3() {
    AssertEqual(IsPalindrom("12"), 0, "Test3-1");
    AssertEqual(IsPalindrom("11"), 1, "Test3-2");
    AssertEqual(IsPalindrom("111"), 1, "Test3-3");

    AssertEqual(IsPalindrom("madam"), 1, "Test3-4");
    AssertEqual(IsPalindrom("level"), 1, "Test3-5");
    AssertEqual(IsPalindrom("wasitacaroracatisaw"), 1, "Test3-6");

    AssertEqual(IsPalindrom("madaam"), 0, "Test3-7");
    AssertEqual(IsPalindrom(" level "), 1, "Test3-8");
    AssertEqual(IsPalindrom("  wasitacaroracatisaw  "), 1, "Test3-9");

    AssertEqual(IsPalindrom("      "), 1, "Test3-10");

    AssertEqual(IsPalindrom(".  ."), 1, "Test3-11");
}

void Test4() {
    AssertEqual(IsPalindrom("1121"), 0, "Test4-1");
    AssertEqual(IsPalindrom("1211"), 0, "Test4-2");
    AssertEqual(IsPalindrom(" 11"), 0, "Test4-3");
}

void Test5() {
    AssertEqual(IsPalindrom("1234321"), 1, "Test5-1");
    AssertEqual(IsPalindrom("123421"), 0, "Test5-2");
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(Test1, "Test1");
    tr.RunTest(Test2, "Test2");
    tr.RunTest(Test3, "Test3");
    tr.RunTest(Test4, "Test4");
    tr.RunTest(Test5, "Test5");
}

int main() {
    TestAll();
    return 0;
}