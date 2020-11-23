/*	Реализуйте рассказанный на лекции класс Function, позволяющий создавать, вычислять и 
	инвертировать функцию, состоящую из следующих элементарных операций:
		- прибавить вещественное число x;
		- вычесть вещественное число x.
	При этом необходимо объявить константными все методы, которые по сути такими являются.

	Замечание
	Более детальное описание задачи с подробным разбором реализации вышеуказанного класса приводится в двух предшествующих видеолекциях.
	На проверку пришлите файл, содержащий реализацию вышеуказанного класса Function. */

#include <iostream>
#include <vector>

using namespace std;

class FunctionPart {
	char operation;
	double value;
public:
	FunctionPart(char op, double val) : operation(op), value(val) {}
	double Apply(double sourceVal) const {
		switch (operation) {
		case '+': return sourceVal += value;
		case '-': return sourceVal -= value;
		case '*': return sourceVal *= value;
		case '/': return sourceVal /= value;
		}
		return -1;
	}
	void Invert() {
		switch (operation) {
		case '+': operation = '-'; break;
		case '-': operation = '+'; break;
		case '*': operation = '/'; break;
		case '/': operation = '*'; break;
		}
	}
};

class Function {
	vector<FunctionPart> operations;
public:
	void AddPart(char op, double val) {
		operations.push_back({ op, val });
	}
	void Invert() {
		for (FunctionPart& o : operations) {
			o.Invert();
		}
		reverse(begin(operations), end(operations));
	};
	double Apply(double initialValue) const {
		for (auto o : operations) {
			initialValue = o.Apply(initialValue);
		}
		return initialValue;
	};
};