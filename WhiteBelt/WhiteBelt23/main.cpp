/* �������� �������, �������
	- ���������� PalindromFilter
	- ���������� vector<string>
	- ��������� vector<string> words � int minLength � ���������� ��� ������ �� ������� words, 
	  ������� �������� ������������ � ����� ����� �� ������ minLength
������� ������ �������� �� ����� 100 �����, ����� ������ ������ �� ������ 100 ��������.
*/
#include <string>
#include <vector>

using namespace std;

bool IsPalindrom(string word) {
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

vector<string> PalindromFilter(vector<string> words, int minLength) {
	vector<string> answer;
	for (auto w: words) {
		if (IsPalindrom(w) && w.length() >= minLength) {
			answer.push_back(w);
		}
	}
	return answer;
}