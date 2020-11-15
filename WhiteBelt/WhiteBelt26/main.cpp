/* Реализуйте функцию void Reverse(vector<int>& v), 
которая переставляет элементы вектора в обратном порядке. */

#include <vector>

using namespace std;

void Reverse(vector<int>& v) {
	int temp;
	for (size_t i = 0; i < v.size() / 2; i++) {
		temp = v[i];
		v[i] = v[v.size() - 1 - i];
		v[v.size() - 1 - i] = temp;
	}
}