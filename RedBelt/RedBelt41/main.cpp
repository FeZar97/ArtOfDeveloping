#include <iostream>
#include <list>
#include <map>

using namespace std;

int main() {
	int n, n1, n2;
	list<int>::const_iterator insertPos;

	list<int> playersOrder;
	map<int, list<int>::const_iterator> listIterators;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> n1 >> n2;

		if (listIterators.count(n2)) {
			insertPos = listIterators[n2];
		}
		else {
			insertPos = playersOrder.end();
		}
		listIterators[n1] = playersOrder.insert(insertPos, n1);
	}

	for (int player: playersOrder) {
		cout << player << "\n";
	}
}