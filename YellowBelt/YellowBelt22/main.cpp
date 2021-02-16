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

// int GetDistinctRealRootCount(double a, double b, double c);

void LinearEquation() {
    AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "LinearEquation");
}

void NotIntersectedParabola() {
    AssertEqual(GetDistinctRealRootCount(1, 1, 1), 0, "PositiveQuadroEquation1");
    AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0, "PositiveQuadroEquation2");

    AssertEqual(GetDistinctRealRootCount(-1, -1, -1), 0, "NegativeQuadroEquation1");
    AssertEqual(GetDistinctRealRootCount(-1, 0, -1), 0, "NegativeQuadroEquation2");
}

void OneExistingRoot() {
    AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "OneExistingRoot1");
    AssertEqual(GetDistinctRealRootCount(-1, 0, 0), 1, "OneExistingRoot2");
}

void StandardQuadro() {
    AssertEqual(GetDistinctRealRootCount(1, 1, -1), 2, "StandardQuadro1");
    AssertEqual(GetDistinctRealRootCount(1, 0, -1), 2, "StandardQuadro2");
    AssertEqual(GetDistinctRealRootCount(-1, -1, 1), 2, "StandardQuadro3");
    AssertEqual(GetDistinctRealRootCount(-1, 0, 1), 2, "StandardQuadro4");
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(LinearEquation, "LinearEquation");
    tr.RunTest(NotIntersectedParabola, "NotIntersectedParabola");
    tr.RunTest(OneExistingRoot, "OneExistingRoot");
    tr.RunTest(StandardQuadro, "StandardQuadro");
}

int main() {
    TestAll();
    return 0;
}