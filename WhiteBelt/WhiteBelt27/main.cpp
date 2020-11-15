/* ���������� ������� vector<int> Reversed(const vector<int>& v), 
������������ ����� ������� v, � ������� ����� ������������ � �������� �������. */

#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
	vector<int> result;
	if (!v.empty()) {
		for (size_t i = 0; i < v.size(); i++) {
			result.push_back(v[v.size() - 1 - i]);
		}
	}
	return result;
}