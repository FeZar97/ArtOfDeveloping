/* В стандартном потоке даны три строки, разделённые пробелом. 
Каждая строка состоит из строчных латинских букв и имеет длину 
не более 30 символов. Выведите в стандартный вывод лексикографически 
минимальную из них. */
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	vector<string> v{ 3 };
	for (int i = 0; i < 3; i++) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	cout << v[0];
	return 0;
}