/*	В файле input.txt записаны вещественные числа, по одному на строчку. 
	На стандартный вывод напечатайте эти числа в том же порядке, по одному на строке, 
	но сделайте так, чтобы у каждого из них было ровно три знака после десятичной точки. */
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
	ifstream is("input.txt");
	cout << fixed << setprecision(3);
	double val;

	while (is >> val) {
		cout << val << endl;
	}

	return 0;
}