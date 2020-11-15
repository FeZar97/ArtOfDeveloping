/*	Напишите функцию BuildMapValuesSet, принимающую на вход 
	словарь map<int, string> и возвращающую множество значений этого словаря:

		set<string> BuildMapValuesSet(const map<int, string>& m) {
			// ...
		}
*/
#include <string>
#include <map>
#include <set>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
	set<string> result;
	for (auto v : m) {
		result.insert(v.second);
	}
	return result;
}