/*	�������� �������

	void EnsureEqual(const string& left, const string& right);

	� ������, ���� ������ left �� ����� ������ right, ������� ������ ����������� ���������� runtime_error 
	� ����������� "<l> != <r>", ��� <l> � <r> - ������, ������� �������� � ���������� left � right ��������������. 
	�������� ��������, ��� ������ ����� ����������� � ������, ������� ���������� � ����������, ������ ���� ����� �� ������ �������.

	���� left == right, ������� ������ ��������� �����������. */
#include <iostream>
#include <sstream>

using namespace std;

void EnsureEqual(const string& left, const string& right) {
	if (left != right) {
		throw runtime_error(left + " != " + right);
	}
}

int main() {
	try {
		EnsureEqual("C++ White", "C++ White");
		EnsureEqual("C++ White", "C++ Yellow");
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}
	return 0;
}