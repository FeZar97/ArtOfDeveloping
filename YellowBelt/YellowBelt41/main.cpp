#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*  Напишите функцию PrintVectorPart, принимающую вектор целых чисел numbers, 
	выполняющую поиск первого отрицательного числа в нём и выводящую в 
	стандартный вывод все числа, расположенные левее найденного, в обратном порядке. 
	Если вектор не содержит отрицательных чисел, выведите все числа в обратном порядке. */

void PrintVectorPart(const vector<int>& numbers) {
	auto it = find_if(begin(numbers), end(numbers),
		[](int number) {
			return number < 0;
		});

	while (it != begin(numbers)) {
		it--;
		cout << *it << " ";
	}
}
/*
int main() {

	PrintVectorPart({ 6, 1, 8, -5, 4 }); // 8 1 6
	cout << endl;
	PrintVectorPart({ -6, 1, 8, -5, 4 });  // ничего не выведется
	cout << endl;
	PrintVectorPart({ 6, 1, 8, 5, 4 }); // 4 5 8 1 6
	cout << endl;

	return 0;
}
*/