#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void printPermutations(int number) {
	vector<int> startPermutation;
	for (int i = number; i >= 1; i--) {
		startPermutation.push_back(i);
	}

	do {
		for (auto n : startPermutation) {
			cout << n << " ";
		}
		cout << endl;
	} while (prev_permutation(begin(startPermutation), end(startPermutation)));
}

int main() {
	int n;
	cin >> n;
	printPermutations(n);
}