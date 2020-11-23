/*	»так, теперь у нас с вами есть полноценный тип дл€ представлени€ обыкновенных дробей: 
	класс Rational интегрирован в €зык с помощью перегрузки операторов и не позвол€ет выполн€ть
	некорректные операции за счЄт выбрасывани€ исключений. ƒавайте на основе класса Rational 
	создадим простой калькул€тор дл€ обыкновенных дробей.
	
	¬ам надо написать программу, котора€ считывает из стандартного ввода одну строку в 
	формате ƒ–ќЅ№_1 операци€ ƒ–ќЅ№_2. 
	ƒ–ќЅ№_1 и ƒ–ќЅ№_2 имеют формат X/Y, где X Ч целое, а Y Ч целое неотрицательное число. 
	операци€ Ч это один из символов '+', '-', '*', '/'.

	≈сли ƒ–ќЅ№_1 или ƒ–ќЅ№_2 €вл€етс€ некорректной обыкновенной дробью, ваша программа должна 
	вывести в стандартный вывод сообщение "Invalid argument". ≈сли считанна€ операци€ Ч это деление на ноль, 
	выведите в стандартный вывод сообщение "Division by zero". ¬ противном случае выведите результат операции. */

#include <iostream>
#include <sstream>
#include <numeric>
#include <exception>

using namespace std;

class Rational {
	int numerator;
	int denominator;
public:
	Rational() : numerator(0), denominator(1) {}
	Rational(int _numerator, int _denominator) {

		if (_denominator == 0) {
			throw runtime_error("Invalid argument");
		}

		int gcd = std::gcd(_numerator, _denominator);
		if (gcd > 1) {
			_numerator /= gcd;
			_denominator /= gcd;
		}

		if (double(_numerator) / double(_denominator) < 0) {
			numerator = -abs(_numerator);
			denominator = abs(_denominator);
		}
		else if (double(_numerator) / double(_denominator) == 0) {
			numerator = 0;
			denominator = 1;
		}
		else {
			numerator = abs(_numerator);
			denominator = abs(_denominator);
		}
	}

	int Numerator() const {
		return numerator;
	}

	int Denominator() const {
		return denominator;
	}

	friend Rational operator+(const Rational &lhs, const Rational &rhs) {
		Rational res(lhs.numerator*rhs.denominator + rhs.numerator*lhs.denominator,
			lhs.denominator * rhs.denominator);
		return res;
	}

	friend Rational operator-(const Rational &lhs, const Rational &rhs) {
		return lhs + Rational(-rhs.numerator, rhs.denominator);
	}

	friend bool operator==(const Rational &lhs, const Rational &rhs) {
		return ((lhs.numerator == rhs.numerator) && (lhs.denominator == rhs.denominator));
	}

	friend Rational operator*(const Rational &lhs, const Rational &rhs) {
		return Rational(lhs.numerator * rhs.numerator,
			lhs.denominator * rhs.denominator);
	}

	friend Rational operator/(const Rational &lhs, const Rational &rhs) {
		if (rhs.Numerator() == 0) throw runtime_error("Division by zero");
		return Rational(lhs.numerator * rhs.denominator,
			lhs.denominator * rhs.numerator);
	}

	friend istream& operator>>(istream& is, Rational &in) {
		int num, denom;
		char delim;
		is >> num >> delim >> denom;

		if (delim != '/') throw runtime_error("Invalid argument");
		if (!is.fail()) {
			in = Rational(num, denom);
		}
		return is;
	}

	friend ostream& operator<<(ostream& os, const Rational &out) {
		os << out.Numerator() << "/" << out.Denominator();
		return os;
	}

	friend bool operator>(const Rational &lhs, const Rational &rhs) {
		return lhs.numerator * rhs.denominator > rhs.numerator * lhs.denominator;
	}
	friend bool operator<(const Rational &lhs, const Rational &rhs) {
		return rhs > lhs;
	}
};

int main() {
	Rational r1, r2, res;
	char operation;

	try {
		cin >> r1;
		cin.ignore(1);
		cin >> operation;
		cin.ignore(1);
		cin >> r2;

		switch (operation) {
			case '+':
				res = r1 + r2;
				break;
			case '-':
				res = r1 - r2;
				break;
			case '*':
				res = r1 * r2;
				break;
			case '/':
				res = r1 / r2;
				break;
		}
		cout << res;
	}
	catch(exception &ex) {
		cout << ex.what();
	}

	return 0;
}