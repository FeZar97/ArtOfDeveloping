﻿/* Даны значения температуры, наблюдавшиеся в течение N подряд идущих дней. 
Найдите номера дней (в нумерации с нуля) со значением температуры выше среднего арифметического за все N дней.

Гарантируется, что среднее арифметическое значений температуры является целым числом.

Формат ввода
	Вводится число N, затем N неотрицательных целых чисел — значения температуры в 0-й, 1-й, ... (N−1)-й день.

Формат вывода
	Первое число K — количество дней, значение температуры в которых выше среднего арифметического. Затем K целых чисел — номера этих дней.*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, avg = 0;
	cin >> n;
	vector<int> measurments(n), result;

	for (int i = 0; i < n; i++) {
		cin >> measurments[i];
		avg += measurments[i];
	}
	avg /= n;

	for (int i = 0; i < n; i++) {
		if (measurments[i] > avg) {
			result.push_back(i);
		}
	}

	cout << result.size() << endl;
	for (auto r : result) {
		cout << r << endl;
	}

	return 0;
}