#include <algorithm>
#include <memory>
#include <vector>

#include "../test_runner.h"

using namespace std;

template <typename RandomIt>
using Value = typename RandomIt::value_type;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {

	if (distance(range_begin, range_end) < 2) {
		return;
	}

	vector<Value<RandomIt>> tempVector(make_move_iterator(range_begin), make_move_iterator(range_end));

	size_t vecLength = tempVector.size();

	auto firstIt = tempVector.begin() + vecLength / 3,
		 secondIt = tempVector.begin() + 2 * vecLength / 3;

	MergeSort(tempVector.begin(), firstIt);
	MergeSort(firstIt, secondIt);
	MergeSort(secondIt, tempVector.end());

	vector<Value<RandomIt>> resultVec;
	merge(make_move_iterator(tempVector.begin()), make_move_iterator(firstIt),
		make_move_iterator(firstIt), make_move_iterator(secondIt),
		back_inserter(resultVec));
	
	merge(make_move_iterator(resultVec.begin()), make_move_iterator(resultVec.end()),
		make_move_iterator(secondIt), make_move_iterator(tempVector.end()),
		range_begin);
}

void TestIntVector() {
	vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}
