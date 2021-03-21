#include "test_runner.h"

bool AssertEqual(const string& param1, const string& param2, const string& testName) {
	return param1 == param2;
}

bool AssertEqual(const vector<string>& param1, const vector<string>& param2,
	const string& testName) {
	if (param1.size() != param2.size()) {
		return false;
	}

	for (size_t i = 0; i < param1.size(); i++) {
		if (param1[i] != param2[i]) {
			return false;
		}
	}
	return true;
}

TestRunner::~TestRunner() {
	if (fail_count > 0) {
		cerr << fail_count << " unit tests failed. Terminate" << endl;
		exit(1);
	}
}
