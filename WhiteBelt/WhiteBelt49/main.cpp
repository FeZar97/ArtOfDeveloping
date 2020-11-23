/*	� ���� ������ ��� ���� ����������� ����� ��� ������������� ������������ ����� � �������� ��� 
	� ������� ����� ����� �++ ���, ����� �� ����� ���� ������������ ������������ �������. 
	
	������� ������� �� ���������� ������. � ������ ����� �������� ���� � ���������� ���������, 
	������� ����� ��������� ���������

		#include <iostream>
		using namespace std;

		// �����������, ������� �������, ��� ������ ����� ����������� � ���� ���������
		
		int main() {
		    // ����� ����-������ ��� ����� ����������
		    cout << "OK" << endl;
		    return 0;
		}
	��� �����, �� ����� ���� ������� main, ����������� ��, ��� ���������� � ������������, ���, 
	����� ���� ��������� �������� �� ����� ��������� OK. ������� main �������� ��� ����-������, 
	������� ��������� ������������ ����� ����������. ���� ��� ����� ������� ������ � ����� ����������, 
	�� ������ OK ��������� ������� ��������� � ���, ��� ������ �������� �����������.

	����� ���� ��������� ����� �������� OK, ������ ���������� ���� ���� �� ��������. ���� ���������� ����� 
	������������� �� ������, ����� ������ ������ ������. �� ����, ���� ���� ��������� ������� OK, �� ��� �� 
	��� ��������, ��� ���� ���������� ����� ������� ����������� ��������. � ������ ��������� ������� ����������� 
	������� ����� ������ ��� ��������� � ���, ����� ������ ����� ���������� �������� �����������.

	����������� ������� ����� ����-������ ��� ������ ��������� �������. ����� ��������� ����������, ������������� 
	� ����� ����������, ������� ����� ���� �� ������� � ������� �����

	�� �������� ����� ���������� ���� ���� � ����� �����������: ������� main ������� �� ���� �� �����.

	����� 1
	� ������ ����� ��� ���� ����������� ����� Rational, ������� ������������ ����� ������������ ����� ���� p/q, 
	��� p � �����, � q � ����������� � ��������� ��������� �������� p, q ������, ��� ����� ���� ������������ ����� int. 
	��� ����, ����� Rational ������ ����� ��������� ���������:

		class Rational {
		public:
		  Rational();
		  Rational(int numerator, int denominator);
		
		  int Numerator() const;
		  int Denominator() const;
		};

	����� Rational ������ �������������, ��� p/q � ��� ������������ �����.
	������ ����������, ������������� � ���������� ���������� ������ Rational:
		- ����������� �� ��������� ������ ��������� ����� � ���������� 0 � ������������ 1.
		- ��� ��������������� ������ ������ Rational � ����������� p � q ������ ����������� ���������� ����� p/q (����� ��� ����� ����������� ������� ������ ����������� ����� ���������).
		- ���� ����� p/q �������������, �� ������ Rational(p, q) ������ ����� ������������� ��������� � ������������� �����������.
		- ���� ����� p/q �������������, �� ������ Rational(p, q) ������ ����� ������������� ��������� � ����������� (�������� �������� �� ������ Rational(-2, -3)).
		- ���� ��������� ����� ����� ����, �� ����������� ������ ���� ����� 1.
	�������������, ��� �� � ����� �� ������, �� ������� ����� ������������� ���� ����������, �� ����� �����������, ������� ����.

	����� 2
	���������� ��� ������ Rational ��������� ==, + � - ���, ����� �������� � ������� ����� ���� ���������� ������������ �������.

	����� 3
	���������� ���������� �����, ���������� ��������� * � /.

	����� 4
	� ���� ����� ��� ����� ����������� ��������� ����� � ������ ��� ������ Rational.

	����� 5
	�������, ��� ����� ����������� ����������� ������������ ������� ������ Rational � �������� ��������� ���������� set � ������ � ���������� map. */
#include <iostream>
#include <sstream>
#include <numeric>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Rational {
	int numerator;
	int denominator;
public:
	Rational(): numerator(0), denominator(1) {}
	Rational(int _numerator, int _denominator) {
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

	// part 2
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

	// part 3
	friend Rational operator*(const Rational &lhs, const Rational &rhs) {
		return Rational(lhs.numerator * rhs.numerator,
			lhs.denominator * rhs.denominator);
	}

	friend Rational operator/(const Rational &lhs, const Rational &rhs) {
		return Rational(lhs.numerator * rhs.denominator,
			lhs.denominator * rhs.numerator);
	}

	// part 4
	friend istream& operator>>(istream& is, Rational &in) {
		int num, denom;
		char delim;
		is >> num >> delim >> denom;
		if (!is.fail() && delim == '/') {
			in = Rational(num, denom);
		}
		return is;
	}

	friend ostream& operator<<(ostream& os, const Rational &out) {
		os << out.Numerator() << "/" << out.Denominator();
		return os;
	}

	// part 5
	friend bool operator>(const Rational &lhs, const Rational &rhs) {
		return lhs.numerator * rhs.denominator > rhs.numerator * lhs.denominator;
	}
	friend bool operator<(const Rational &lhs, const Rational &rhs) {
		return rhs > lhs;
	}
};

int main() {

	// part 1
	{
		const Rational r(3, 10);
		if (r.Numerator() != 3 || r.Denominator() != 10) {
			cout << "Rational(3, 10) != 3/10" << endl;
			return 1;
		}
	}

	{
		const Rational r(8, 12);
		if (r.Numerator() != 2 || r.Denominator() != 3) {
			cout << "Rational(8, 12) != 2/3" << endl;
			return 2;
		}
	}

	{
		const Rational r(-4, 6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(-4, 6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(4, -6);
		if (r.Numerator() != -2 || r.Denominator() != 3) {
			cout << "Rational(4, -6) != -2/3" << endl;
			return 3;
		}
	}

	{
		const Rational r(0, 15);
		if (r.Numerator() != 0 || r.Denominator() != 1) {
			cout << "Rational(0, 15) != 0/1" << endl;
			return 4;
		}
	}

	{
		const Rational defaultConstructed;
		if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
			cout << "Rational() != 0/1" << endl;
			return 5;
		}
	}

	// part 2
	{
		Rational r1(4, 6);
		Rational r2(2, 3);
		bool equal = r1 == r2;
		if (!equal) {
			cout << "4/6 != 2/3" << endl;
			return 6;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a + b;
		bool equal = c == Rational(2, 1);
		if (!equal) {
			cout << "2/3 + 4/3 != 2" << endl;
			return 7;
		}
	}

	// part 3
	{
		Rational a(5, 7);
		Rational b(2, 9);
		Rational c = a - b;
		bool equal = c == Rational(31, 63);
		if (!equal) {
			cout << "5/7 - 2/9 != 31/63" << endl;
			return 8;
		}
	}

	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal) {
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 9;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal) {
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 10;
		}
	}

	// part 4
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4") {
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 11;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal) {
			cout << "5/7 is incorrectly read as " << r << endl;
			return 12;
		}
	}

	{
		istringstream input("");
		Rational r;
		bool correct = !(input >> r);
		if (!correct) {
			cout << "Read from empty stream works incorrectly" << endl;
			return 13;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 14;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct) {
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 15;
		}
	}

	{
		istringstream input1("1*2"), input2("1/"), input3("/4");
		Rational r1, r2, r3;
		input1 >> r1;
		input2 >> r2;
		input3 >> r3;
		bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
		if (!correct) {
			cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
				<< r1 << " " << r2 << " " << r3 << endl;

			return 16;
		}
	}

	// part 5
	{
		const set<Rational> rs = { {1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2} };
		if (rs.size() != 3) {
			cout << "Wrong amount of items in the set" << endl;
			return 17;
		}

		vector<Rational> v;
		for (auto x : rs) {
			v.push_back(x);
		}
		if (v != vector<Rational>{ {1, 25}, { 1, 2 }, { 3, 4 }}) {
			cout << "Rationals comparison works incorrectly" << endl;
			return 18;
		}
	}

	{
		map<Rational, int> count;
		++count[{1, 2}];
		++count[{1, 2}];

		++count[{2, 3}];

		if (count.size() != 2) {
			cout << "Wrong amount of items in the map" << endl;
			return 19;
		}
	}

	cout << "OK" << endl;
	return 0;
}