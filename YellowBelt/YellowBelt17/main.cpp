#include <map>
#include <iostream>
#include <exception>

using namespace std;

template<typename Key, typename Value>
Value& GetRefStrict(map<Key, Value>& someMap, const Key& key) {
	if (!someMap.count(key)) {
		throw runtime_error("");
	}
	
	return someMap[key];
}

int main() {
	map<int, string> m = { {0, "value"} };

	string& item = GetRefStrict(m, 0);
	item = "newvalue";

	cout << m[0] << endl; // выведет newvalue

	return 0;
}