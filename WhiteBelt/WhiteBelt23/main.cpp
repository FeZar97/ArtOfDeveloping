/* Напишите функцию, которая
	- называется PalindromFilter
	- возвращает vector<string>
	- принимает vector<string> words и int minLength и возвращает все строки из вектора words, 
	  которые являются палиндромами и имеют длину не меньше minLength
Входной вектор содержит не более 100 строк, длина каждой строки не больше 100 символов.
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