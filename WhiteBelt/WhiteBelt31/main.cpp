/*	В стандартном потоке дана одна строка, состоящая из N + 1 целых чисел. 
	Первым числом идёт само число N. Далее следуют ещё N чисел, обозначим их за массив A. 
	Между собой числа разделены пробелом.
	Отсортируйте массив А по модулю и выведите его в стандартный поток. */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int n;
	vector<int> v;

	cin >> n;
	v.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	sort(v.begin(), v.end(), [](int a, int b) {
		return abs(a) < abs(b);
	});

	for (auto i: v) {
		cout << i << " ";
	}

	return 0;
}