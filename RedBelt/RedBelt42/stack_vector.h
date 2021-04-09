#pragma once

#include <array>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>
class StackVector {
	size_t curSize{ 0 };
	array<T, N> data;

public:
	explicit StackVector(size_t a_size = 0) {
		if (a_size > Capacity()) {
			throw invalid_argument("invalid size in ctor");
		}
		curSize = a_size;
	}
	
	T& operator[](size_t index) {
		return data[index];
	}

	const T& operator[](size_t index) const {
		return data[index];
	}
	
	T* begin() {
		return data.begin();
	}
	T* end() {
		return data.begin() + curSize;
	}
	const T* begin() const {
		return data.begin();
	}
	const T* end() const {
		return data.begin() + curSize;
	}
	
	size_t Size() const {
		return curSize;
	}
	size_t Capacity() const {
		return data.max_size();
	}
	
	void PushBack(const T& value) {
		if (Size() == Capacity()) {
			throw overflow_error("overflow_error in PushBack");
		}
		data[curSize++] = value;
	}
	T PopBack() {
		if (curSize == 0) {
			throw underflow_error("underflow_error in PushBack");
		}
		return data[--curSize];
	}
};

