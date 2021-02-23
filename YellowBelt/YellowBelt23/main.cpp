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
class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
    }
    void ChangeLastName(int year, const string& last_name) {
    }
    string GetFullName(int year) {
    }
};
*/

void Test1() {
    Person person;
    string answer1, answer2 = "Incognito Polina with unknown last name Polina Sergeeva ";

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");

    for (int year : {1900, 1965, 1990}) {
        answer1 += person.GetFullName(year) + " ";
    }

    AssertEqual(answer1, answer2, "Test1");
}

void Test2() {
    Person person;
    string answer1, answer2 = "Incognito";

    answer1 = person.GetFullName(1);

    AssertEqual(answer1, answer2, "Test2");
}

void Test3() {
    Person person;
    string answer1, answer2 = "Polina with unknown last name";

    person.ChangeFirstName(1965, "Polina");
    answer1 = person.GetFullName(1965);

    AssertEqual(answer1, answer2, "Test3");
}

void Test4() {
    Person person;
    string answer1, answer2 = "Polina with unknown first name";

    person.ChangeLastName(1965, "Polina");
    answer1 = person.GetFullName(1965);

    AssertEqual(answer1, answer2, "Test4");
}

void Test5() {
    Person person;
    string answer1 = "",
        answer2 = "Incognito Name1 with unknown last name Name1 Name2";

    answer1 += person.GetFullName(1965) + " ";

    person.ChangeFirstName(1965, "Name1");
    answer1 += person.GetFullName(1965) + " ";

    person.ChangeLastName(1966, "Name2");
    answer1 += person.GetFullName(1966);

    AssertEqual(answer1, answer2, "Test5");
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