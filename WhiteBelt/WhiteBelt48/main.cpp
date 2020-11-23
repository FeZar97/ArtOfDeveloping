/*	ќпределите структуру Ђ—тудентї со следующими пол€ми: им€, фамили€, день, мес€ц и год рождени€. 
	—оздайте вектор из таких структур, заполните его из входных данных и затем по запросам выведите нужные пол€.

	‘ормат ввода
	ѕерва€ строка содержит одно целое число N от 0 до 10000 Ч число студентов.
	ƒалее идут N строк, кажда€ из которых содержит две строки длиной от 1 до 15 символов Ч им€ и фамилию 
	очередного студента, и три целых числа от 0 до 1000000000 Ч день, мес€ц и год рождени€.
	—ледующа€ строка содержит одно целое число M от 0 до 10000 Ч число запросов.
	—ледующие M строк содержат строку длиной от 1 до 15 символов Ч запрос, и целое число от 0 до 1000000000 Ч номер студента (нумераци€ начинаетс€ с 1).

	‘ормат вывода
	ƒл€ запроса вида name K, где K от 1 до N, выведите через пробел им€ и фамилию K-го студента.
	ƒл€ запроса вида date K, где K от 1 до N, выведите через точку день, мес€ц и год рождени€ K-го студента.
	ƒл€ остальных запросов выведите bad request. */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
	string firstName;
	string secondName;
	int day;
	int month;
	int year;
};

int main() {
	vector<Student> students;
	Student tempStudent;
	int n, m, k;
	string requestType;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> tempStudent.firstName >> tempStudent.secondName >> tempStudent.day >> tempStudent.month >> tempStudent.year;
		students.push_back(tempStudent);
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> requestType >> k;

		if (requestType == "name") {
			if (k < 1 || k > students.size()) {
				cout << "bad request" << endl;
			}
			else {
				cout << students[k - 1].firstName << " " << students[k - 1].secondName << endl;
			}
		}
		else if (requestType == "date") {
			if (k < 1 || k > students.size()) {
				cout << "bad request" << endl;
			}
			else {
				cout << students[k - 1].day << "." << students[k - 1].month << "." << students[k - 1].year << endl;
			}
		}
		else {
			cout << "bad request" << endl;
		}
	}

	return 0;
}