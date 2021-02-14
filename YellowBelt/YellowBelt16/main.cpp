#include <vector>
#include <map>
#include <iostream>

using namespace std;

// definition
template<typename T>
T Sqr(const T& someVal);

template<typename T>
vector<T> Sqr(const vector<T>& someVec);

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& someMap);

template<typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& somePair);

// realisation
template<typename T>
T Sqr(const T& someVal) {
	return someVal * someVal;
}

template<typename T>
vector<T> Sqr(const vector<T>& someVec) {
	vector<T> result;
	for (auto someVecVal : someVec) {
		result.push_back(Sqr(someVecVal));
	}
	return result;
}

template<typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& someMap) {
	map<Key, Value> result;
	for (const pair<Key, Value>& someMapVal : someMap) {
		result.insert({ someMapVal.first, Sqr(someMapVal.second) });
	}
	return result;
}

template<typename Key, typename Value>
pair<Key, Value> Sqr(const pair<Key, Value>& somePair) {
	return { Sqr(somePair.first), Sqr(somePair.second) };
}

int main() {

	vector<int> v = { 1, 2, 3 };
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
	  {4, {2, 2}},
	  {7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}