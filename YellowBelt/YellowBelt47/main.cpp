#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {

	size_t elemNb = distance(range_begin, range_end);

	if (elemNb < 2) {
		return;
	}

	vector<typename RandomIt::value_type> elements(range_begin, range_end), tempVector;

	auto part1It = begin(elements) + elemNb / 3;
	auto part2It = begin(elements) + 2 * elemNb / 3;

	MergeSort(begin(elements), part1It);
	MergeSort(part1It, part2It);
	MergeSort(part2It, end(elements));

	merge(begin(elements), part1It, part1It, part2It, back_inserter(tempVector));
	merge(begin(tempVector), end(tempVector), part2It, end(elements), range_begin);
}

int main() {
	vector<int> v = { 6, 4, 7, 6, 4, 4, 0, 1 };
	MergeSort(begin(v), end(v));
	for (int x : v) {
		cout << x << " ";
	}
	cout << endl;
	return 0;
}