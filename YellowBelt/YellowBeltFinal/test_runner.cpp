#include "test_runner.h"

bool operator==(const vector<string>& param1, const vector<string>& param2) {
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
