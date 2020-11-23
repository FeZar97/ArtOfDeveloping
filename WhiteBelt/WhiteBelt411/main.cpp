/*	¬спомним класс Rational, который мы реализовали в задачах, посв€щЄнных перегрузке операторов. 
	“ам специально говорилось, что в тестах объекты класса Rational никогда не создаютс€ с нулевым знаменателем 
	и никогда не выполн€етс€ деление на ноль. Ќастало врем€ избавитьс€ от этого ограничени€ и научитьс€ обрабатывать 
	нулевой знаменатель и деление на ноль. ¬ этой задаче вам предстоит это сделать.

	ѕомен€йте реализацию конструктора класса Rational так, чтобы он выбрасывал исключение invalid_argument, 
	если знаменатель равен нулю.  роме того, переделайте реализацию оператора делени€ дл€ класса Rational так,
	чтобы он выбрасывал исключение domain_error, если делитель равен нулю. */
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
			throw invalid_argument("invalid argument in Rational(n,d)");
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

	friend Rational operator*(const Rational &lhs, const Rational &rhs) {
		return Rational(lhs.numerator * rhs.numerator,
			lhs.denominator * rhs.denominator);
	}

	friend Rational operator/(const Rational &lhs, const Rational &rhs) {
		if (rhs.Numerator() == 0) throw domain_error("error in operator '/'");
		return Rational(lhs.numerator * rhs.denominator,
			lhs.denominator * rhs.numerator);
	}
};

int main() {

	try {
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument&) {
	}

	try {
		auto x = Rational(1, 2) / Rational(0, 1);
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error&) {
	}

	cout << "OK" << endl;

	return 0;
}