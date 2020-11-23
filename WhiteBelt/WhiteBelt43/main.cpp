/*	Добавьте в класс Function из задачи «Обратимая функция» обработку умножения ('*')
	и деления ('/'). Гарантируется отсутствие элементарных операций умножения и деления на 0. */
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