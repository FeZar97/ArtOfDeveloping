#pragma once

#include <cstdlib>
#include <cstring>
#include <algorithm>

template <typename T>
class SimpleVector {

	size_t size_;
	size_t capacity_;
	T* data;

public:
	SimpleVector() {
		size_ = 0;
		capacity_ = 0;
		data = nullptr;
	}

	explicit SimpleVector(size_t size) {
		capacity_ = size;
		size_ = size;
		data = new T[size];
	}

	SimpleVector(const SimpleVector<T>& other) {
		size_ = other.size_;
		capacity_ = other.capacity_;
		data = new T[size_];
		std::copy(other.begin(), other.end(), data);
	}

	~SimpleVector() {
		if (data) {
			delete[] data;
		}
	}

	T& operator[](size_t index) {
		return data[index];
	}

	T* begin() {
		return data;
	}

	T* end() {
		return data + size_;
	}

	T* begin() const {
		return data;
	}

	T* end() const {
		return data + size_;
	}

	size_t Size() const {
		return size_;
	}

	size_t Capacity() const {
		return capacity_;
	}

	void PushBack(const T& value) {
		if (size_ >= capacity_) {
			auto new_cap = capacity_ == 0 ? 1 : 2 * capacity_;
			auto new_data = new T[new_cap];
			std::copy(begin(), end(), new_data);
			delete[] data;
			data = new_data;
			capacity_ = new_cap;
		}
		data[size_++] = value;
	}

	SimpleVector& operator=(const SimpleVector& vec) {

		if (&vec == this) {
			return *this;
		}

		SimpleVector<T> tmp(vec);
		std::swap(tmp.data, data);
		std::swap(tmp.size_, size_);
		std::swap(tmp.capacity_, capacity_);

		return *this;
	}
};
