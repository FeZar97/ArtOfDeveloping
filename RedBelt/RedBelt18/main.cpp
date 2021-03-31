#include <vector>
#include <stdexcept>

// #include "../test_runner.h"

using namespace std;

template<typename T>
class Deque {
	vector<T> forwardVec;
	vector<T> backwardVec;

	T& getElem(size_t index) {
		if (index < forwardVec.size()) {
			return forwardVec[forwardVec.size() - 1 - index];
		}
		else if (index < Size()) {
			return backwardVec[index - forwardVec.size()];
		}
		throw out_of_range("");
	}

	const T& getElemC(size_t index) const {
		if (index < forwardVec.size()) {
			return forwardVec[forwardVec.size() - 1 - index];
		}
		else if (index < Size()) {
			return backwardVec[index - forwardVec.size()];
		}
		throw out_of_range("");
	}

public:
	Deque() {};

	size_t Size() const {
		return forwardVec.size() + backwardVec.size();
	}

	bool Empty() const {
		return (Size() == 0);
	}

	// operator []
	T& operator[](size_t index) {
		return getElem(index);
	}

	const T& operator[](size_t index) const {
		return getElemC(index);
	}

	// AT
	T& At(size_t index) {
		if (index < 0 || index >= Size()) {
			throw out_of_range("");
		}
		return getElem(index);
	}

	const T& At(size_t index) const {
		if (index < 0 || index >= Size()) {
			throw out_of_range("");
		}
		return getElemC(index);
	}

	// FRONT
	T& Front() {
		return getElem(0);
	}

	const T& Front() const {
		return getElemC(0);
	}

	// BACK
	T& Back() {
		return getElem(Size() - 1);
	}

	const T& Back() const {
		return getElemC(Size() - 1);
	}

	void PushFront(const T& elem) {
		forwardVec.push_back(elem);
	}
	
	void PushBack(const T& elem) {
		backwardVec.push_back(elem);
	}
};

/*
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

	deq.PushBack(11);
	int lastIdx = deq.Size() - 1;
	int lastElem = deq[lastIdx];
	ASSERT_EQUAL(lastElem, 11);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}
*/