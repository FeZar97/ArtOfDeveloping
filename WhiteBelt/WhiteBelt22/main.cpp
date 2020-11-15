/* Ќапишите функцию, котора€
	- называетс€ IsPalindrom
	- возвращает bool
	- принимает параметр типа string и возвращает, €вл€етс€ ли переданна€ строка палиндромом
	ѕалиндром - это слово или фраза, которые одинаково читаютс€ слева направо и справа налево. ѕуста€ строка €вл€етс€ палиндромом.
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