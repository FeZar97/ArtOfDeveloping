#pragma once

#include <cstdlib>
#include <cstring>

template <typename T>
class SimpleVector {

	size_t size_;
	size_t capacity_;
	T* data;

public:
	SimpleVector() {
		size_ = 0;
		capacity_ = 0 ;
		data = nullptr;
	}

	explicit SimpleVector(size_t size) {
		capacity_ = size;
		size_ = size;
		data = new T[size];
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
	
	size_t Size() const {
		return size_;
	}

	size_t Capacity() const {
		return capacity_;
	}

	void PushBack(const T& value) {
		if (size_ == capacity_) {
			capacity_ *= 2;
			if (!capacity_) {
				capacity_ = 1;
			}
			T* newData = new T[capacity_];
			if (data) {
				memcpy(newData, data, size_ * sizeof(T));
				delete[] data;
			}
			data = newData;
			PushBack(value);
		}
		else {
			data[size_++] = value;
		}
	}
};
