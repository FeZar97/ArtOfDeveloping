/*	�������� ������� BuildMapValuesSet, ����������� �� ���� 
	������� map<int, string> � ������������ ��������� �������� ����� �������:

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