#include <vector>

#include "../test_runner.h"

using namespace std;

template<typename T>
class Deque {
	vector<T> forwardVec;
	vector<T> backwardVec;

public:
	Deque() {};

	bool Empty() const {
		return forwardVec.empty() && backwardVec.empty();
	}

	size_t Size() const {
		return forwardVec.size() + backwardVec.size();
	}

	// operator []
	T& operator[](size_t index) {
		if (index < forwardVec.size()) {
			return forwardVec[index];
		}
		else if (index < Size()) {
			return backwardVec[Size() - index - 1];
		}
	}

	const T& operator[](size_t index) const {
		if (index < forwardVec.size()) {
			return forwardVec[index];
		}
		else if (index < Size()) {
			return backwardVec[Size() - index - 1];
		}
	}

	// AT
	T& At(size_t index) {
		if (index < 0 || index >= Size()) {
			throw out_of_range("");
		}
		if (index < forwardVec.size()) {
			return forwardVec[forwardVec.size() - 1 - index];
		}
		else if (index < Size()) {
			return backwardVec[Size() - index - 1];
		}
	}

	const T& At(size_t index) const {
		if (index < 0 || index >= Size()) {
			throw out_of_range("");
		}
		if (index < forwardVec.size()) {
			return forwardVec[index];
		}
		else if (index < Size()) {
			return backwardVec[Size() - index - 1];
		}
	}

	// FRONT
	T& Front() {
		if (!forwardVec.empty()) {
			return forwardVec[0];
		}
		if (!backwardVec.empty()) {
			return backwardVec[backwardVec.size() - 1];
		}
	}

	const T& Front() const {
		if (!forwardVec.empty()) {
			return forwardVec[0];
		}
		if (!backwardVec.empty()) {
			return backwardVec[backwardVec.size() - 1];
		}
	}

	// BACK
	T& Back() {
		if (!backwardVec.empty()) {
			return backwardVec[0];
		}
		if (!forwardVec.empty()) {
			return forwardVec[forwardVec.size() - 1];
		}
	}

	const T& Back() const {
		if (!backwardVec.empty()) {
			return backwardVec[0];
		}
		if (!forwardVec.empty()) {
			return forwardVec[forwardVec.size() - 1];
		}
	}

	void PushFront(const T& elem) {
		forwardVec.push_back(elem);
	}
	
	void PushBack(const T& elem) {
		backwardVec.push_back(elem);
	}
};

void TestDeque() {
	Deque<int> deq;

	deq.PushBack(1);
	ASSERT_EQUAL(deq.Size(), 1);
	ASSERT_EQUAL(deq[0], 1);

	deq.PushFront(2);
	ASSERT_EQUAL(deq.Size(), 2);
	ASSERT_EQUAL(deq[0], 2);

	deq.PushFront(1);
	ASSERT_EQUAL(deq.Size(), 3);
	ASSERT_EQUAL(deq[0], 1);

	int backElem = deq.Back();
	ASSERT_EQUAL(backElem, 1);

	deq[2] = 7;
	ASSERT_EQUAL(deq.Back(), 7);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}