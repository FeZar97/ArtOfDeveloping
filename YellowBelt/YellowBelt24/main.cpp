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
class Rational {
public:
    Rational();
    Rational(int numerator, int denominator) {
    }

    int Numerator() const {
    }

    int Denominator() const {
    }
};
*/

/*
Список требований, предъявляемых к реализации интерфейса класса Rational:
    1 Конструктор по умолчанию должен создавать дробь с числителем 0 и знаменателем 1.
    2 При конструировании объекта класса Rational с параметрами p и q должно выполняться сокращение дроби p/q.
    3 Если дробь p/q отрицательная, то объект Rational(p, q) должен иметь отрицательный числитель и положительный знаменатель.
    4 Если дробь p/q положительная, то объект Rational(p, q) должен иметь положительные числитель и знаменатель (обратите внимание на случай Rational(-2, -3)).
    5 Если числитель дроби равен нулю, то знаменатель должен быть равен 1.
*/

void Test1() {
    Rational rational;
    AssertEqual(rational.Numerator(), 0, "Test1-1");
    AssertEqual(rational.Denominator(), 1, "Test1-2");
}

void Test2() {
    Rational rational1(1, 1);
    AssertEqual(rational1.Numerator(), 1, "Test2-1");
    AssertEqual(rational1.Denominator(), 1, "Test2-2");

    Rational rational2(-1, 1);
    AssertEqual(rational2.Numerator(), -1, "Test2-3");
    AssertEqual(rational2.Denominator(), 1, "Test2-4");

    Rational rational3(0, 1);
    AssertEqual(rational3.Numerator(), 0, "Test2-5");
    AssertEqual(rational3.Denominator(), 1, "Test2-6");

    Rational rational4(2, 4);
    AssertEqual(rational4.Numerator(), 1, "Test2-7");
    AssertEqual(rational4.Denominator(), 2, "Test2-8");

    Rational rational5(7, -21);
    AssertEqual(rational5.Numerator(), -1, "Test2-9");
    AssertEqual(rational5.Denominator(), 3, "Test2-10");

    Rational rational6(-24, -6);
    AssertEqual(rational6.Numerator(), 4, "Test2-11");
    AssertEqual(rational6.Denominator(), 1, "Test2-12");

    Rational rational7(24, 10);
    AssertEqual(rational7.Numerator(), 12, "Test2-13");
    AssertEqual(rational7.Denominator(), 5, "Test2-14");
}

void Test3() {
    Rational rational1(-1, 1);
    AssertEqual(rational1.Numerator(), -1, "Test3-1");
    AssertEqual(rational1.Denominator(), 1, "Test3-2");

    Rational rational2(1, -1);
    AssertEqual(rational2.Numerator(), -1, "Test3-3");
    AssertEqual(rational2.Denominator(), 1, "Test3-4");
}

void Test4() {
    Rational rational1(1, 1);
    AssertEqual(rational1.Numerator(), 1, "Test4-1");
    AssertEqual(rational1.Denominator(), 1, "Test4-2");

    Rational rational2(-1, -1);
    AssertEqual(rational2.Numerator(), 1, "Test4-3");
    AssertEqual(rational2.Denominator(), 1, "Test4-4");
}

void Test5() {
    Rational rational1(0, 1);
    AssertEqual(rational1.Denominator(), 1, "Test5-1");

    Rational rational2(0, -1);
    AssertEqual(rational2.Denominator(), 1, "Test5-2");
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