/* �������� �������, �������
	- ���������� IsPalindrom
	- ���������� bool
	- ��������� �������� ���� string � ����������, �������� �� ���������� ������ �����������
	��������� - ��� ����� ��� �����, ������� ��������� �������� ����� ������� � ������ ������. ������ ������ �������� �����������.
*/
#include <string>

bool IsPalindrom(std::string word) {
	if (word.length() < 2) {
		return true;
	}
	else {
		for (int i = 0; i < word.length() / 2; i++) {
			if (word.at(i) != word.at(word.length() - 1 - i)) {
				return false;
			}
		}
		return true;
	}
}