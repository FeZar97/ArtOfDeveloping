/* –еализуйте справочник столиц стран.
	Ќа вход программе поступают следующие запросы:
		CHANGE_CAPITAL country new_capital Ч изменение столицы страны country на new_capital, 
											 либо добавление такой страны с такой столицей, если раньше еЄ не было.
		RENAME old_country_name new_country_name Ч переименование страны из old_country_name в new_country_name.
		ABOUT country Ч вывод столицы страны country.
		DUMP Ч вывод столиц всех стран.

‘ормат ввода
	¬ первой строке содержитс€ количество запросов Q, в следующих Q строках Ч описани€ запросов. 
	¬се названи€ стран и столиц состо€т лишь из латинских букв, цифр и символов подчЄркивани€.

‘ормат вывода
	¬ыведите результат обработки каждого запроса:

¬ ответ на запрос CHANGE_CAPITAL country new_capital выведите
	- Introduce new country country with capital new_capital, если страны country раньше не существовало;
	- Country country hasn't changed its capital, если страна country до текущего момента имела столицу new_capital;
	- Country country has changed its capital from old_capital to new_capital, если страна country до текущего 
	  момента имела столицу old_capital, название которой не совпадает с названием new_capital.

¬ ответ на запрос RENAME old_country_name new_country_name выведите
	- Incorrect rename, skip, если новое название страны совпадает со старым, 
	  страна old_country_name не существует или страна new_country_name уже существует;
	- Country old_country_name with capital capital has been renamed to new_country_name, 
	  если запрос корректен и страна имеет столицу capital.

¬ ответ на запрос ABOUT country выведите
	- Country country doesn't exist, если страны с названием country не существует;
	- Country country has capital capital, если страна country существует и имеет столицу capital.

¬ ответ на запрос DUMP выведите
	- There are no countries in the world, если пока не было добавлено ни одной страны;
	- последовательность пар вида country/capital, описывающую столицы всех стран, 
	если в мире уже есть хот€ бы одна страна. ѕри выводе последовательности пары указанного 
	вида необходимо упор€дочить по названию страны и раздел€ть между собой пробелом. */

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	int q;
	string command, temp1, temp2;
	map<string, string> countries;

	cin >> q;

	for (int i = 0; i < q; i++) {
		cin >> command;

		if (command == "CHANGE_CAPITAL") {
			cin >> temp1 >> temp2;
			if (countries.count(temp1) == 0) {
				cout << "Introduce new country " << temp1 << " with capital " << temp2 << endl;
				countries[temp1] = temp2;
			}
			else {
				if (countries[temp1] == temp2) {
					cout << "Country " << temp1 << " hasn't changed its capital" << endl;
				}
				else {
					cout << "Country " << temp1 << " has changed its capital from " << countries[temp1] << " to " << temp2 << endl;
					countries[temp1] = temp2;
				}
			}
		} else if (command == "RENAME") {
			cin >> temp1 >> temp2;
			if ( (countries.count(temp1) == 0) || countries.count(temp2) || (temp1 == temp2) ) {
				cout << "Incorrect rename, skip" << endl;
			}
			else {
				cout << "Country " << temp1 << " with capital " << countries[temp1] << " has been renamed to " << temp2 << endl;
				countries[temp2] = countries[temp1];
				countries.erase(temp1);
			}

		} else if(command == "ABOUT") {
			cin >> temp1;
			if (countries.count(temp1) == 0) {
				cout << "Country " << temp1 << " doesn't exist" << endl;
			}
			else {
				cout << "Country " << temp1 << " has capital " << countries[temp1] << endl;
			}
		}
		else if (command == "DUMP") {
			if (countries.empty()) {
				cout << "There are no countries in the world" << endl;
			}
			else {
				for (auto c : countries) {
					cout << c.first << "/" << c.second << endl;
				}
			}
		}
	}

	return 0;
}