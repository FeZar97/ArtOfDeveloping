#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main() {
	int x, opeationsNb, curNumber, prevPriority = 1, curPriority = 0;
	char curOpeartion;

	deque<string> result;

	cin >> x >> opeationsNb;
	result.push_back(to_string(x));

	while (opeationsNb > 0) {

		cin >> curOpeartion >> curNumber;

		if (curOpeartion == '*' || curOpeartion == '/') {
			curPriority = 1;
		}
		else {
			curPriority = 0;
		}

		if (prevPriority < curPriority) {
			result.push_front("(");
			result.push_back(")");
		}
		prevPriority = curPriority;

		result.push_back(" ");
		result.push_back({ curOpeartion });
		result.push_back(" ");
		result.push_back(to_string(curNumber));

		opeationsNb--;
	}

	for (auto str : result) {
		cout << str;
	}
	cout << endl;

	return 0;
}