#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

#include "../test_runner.h"

using namespace std;

template <class T>
class ObjectPool {
	set<T*> allocatedObjects;
	queue<T*> freeObjects;

public:
	T* Allocate() {
		T* allocatedObject;
		if (!freeObjects.empty()) {
			allocatedObject = freeObjects.front();
			allocatedObjects.insert(allocatedObject);
			freeObjects.pop();
		}
		else {
			allocatedObject = new T;
			allocatedObjects.insert(allocatedObject);
		}
		return allocatedObject;
	}

	T* TryAllocate() {
		if (!freeObjects.empty()) {
			return Allocate();
		}
		return nullptr;
	}

	void Deallocate(T* object) {

		auto findPtrIter = allocatedObjects.find(object);

		if (findPtrIter == allocatedObjects.end()) {
			throw invalid_argument("invalid pointer");
		}
		else {
			freeObjects.push(*findPtrIter);
			allocatedObjects.erase(findPtrIter);
		}
	}

	~ObjectPool() {

		for (auto objectPtrIter : allocatedObjects) {
			delete objectPtrIter;
		}
		allocatedObjects.clear();

		while (!freeObjects.empty()) {
			auto ptr = freeObjects.front();
			delete ptr;
			freeObjects.pop();
		}
	}
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}