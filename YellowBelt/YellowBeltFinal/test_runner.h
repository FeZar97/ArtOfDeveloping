#pragma once
#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <vector>

using namespace std;

bool AssertEqual(const string &param1, const string& param2, 
	const string& testName);
bool AssertEqual(const vector<string>& param1, const vector<string>& param2, 
	const string& testName);

class TestRunner {
	int fail_count{ 0 };

public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (runtime_error& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
	}

	~TestRunner();
};