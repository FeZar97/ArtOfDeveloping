#include <cstdint>
#include <algorithm>

template <typename T>
class SimpleVector {

	size_t size_{ 0 };
	size_t capacity_{ 0 };
	T* data{ nullptr };

public:
	SimpleVector() = default;

	explicit SimpleVector(size_t size): 
		capacity_(size), size_(size), data(new T[size]) {
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

	void PushBack(T value) {
		if (size_ >= capacity_) {
			capacity_ = capacity_ == 0 ? 1 : 2 * capacity_;
			auto newData = new T[capacity_];
			std::move(begin(), end(), newData);
			delete[] data;
			data = newData;
		}

		data[size_++] = std::move(value);
	}
};