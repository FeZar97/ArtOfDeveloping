/*	Условие
	В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. Более подробно, класс Matrix должен иметь:
	- конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
	- конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество строк и столбцов матрицы соответственно
	- метод Reset, принимающий два целочисленных параметра, которые задают новое количество строк и столбцов матрицы соответственно;
	  метод Reset меняет размеры матрицы на заданные и обнуляет все её элементы
	- константный метод At, который принимает номер строки и номер столбца
	  (именно в этом порядке; нумерация строк и столбцов начинается с нуля)
	  и возвращает значение в соответствущей ячейке матрицы
	- неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
	- константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно

	Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset,
	оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.

	Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.

	Кроме того, для класса Matrix должны быть определены следующие операторы:
	- оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов
	  (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки и первого столбца,
	  затем элемент первой строки и второго столбца и так далее
	- оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор
	  ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
	- оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют одинаковый размер
	  и все их соответствующие элементы равны между собой, в противном случае он должен возвращать false.
	- оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является их суммой;
	  если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное исключение invalid_argument.

	Вам дана заготовка решения, а также пример ввода и вывода.
	Когда вы реализуете класс Matrix, вы можете использовать этот пример, чтобы убедиться, что ваш код работает правильно. */
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
	int rows;
	int columns;
	vector<vector<int>> matrix;

public:
	Matrix() {
		rows = 0;
		columns = 0;
	}

	Matrix(int numRows, int numCols) {
		if (numRows < 0 || numCols < 0) {
			throw out_of_range("");
		}
		rows = numRows;
		columns = numCols;
		matrix.resize(numRows);
		for (auto& r : matrix) {
			r.resize(columns);
		}
	}

	void Reset(int numRows, int numCols) {
		*this = Matrix(numRows, numCols);
		for (auto& r : matrix) {
			for (auto& elem : r) {
				elem = 0;
			}
		}
	}

	int At(int row, int column) const {
		if (row < 0 || column < 0 ||
			row >= rows || column >= columns) {
			throw out_of_range("");
		}
		return matrix[row][column];
	}

	int& At(int row, int column) {
		if (row < 0 || column < 0 ||
			row >= rows || column >= columns) {
			throw out_of_range("");
		}
		return matrix[row][column];
	}

	int GetNumRows() const {
		return rows;
	}

	int GetNumColumns() const {
		return columns;
	}

	friend istream& operator>>(istream& is, Matrix& mat) {
		int _row, _column;
		is >> _row >> _column;
		mat.Reset(_row, _column);

		for (int i = 0; i < _row; i++) {
			for (int j = 0; j < _column; j++) {
				is >> mat.matrix[i][j];
			}
		}

		return is;
	}

	friend ostream& operator<<(ostream& os, const Matrix& mat) {
		os << mat.rows << " " << mat.columns << endl;
		for (int i = 0; i < mat.rows; i++) {
			for (int j = 0; j < mat.columns; j++) {
				os << mat.matrix[i][j] << " ";
			}
			os << endl;
		}

		return os;
	}

	friend bool operator==(const Matrix& lhs, const Matrix& rhs) {
		if ((lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0)
			&&
			(rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0)
			) {
			return true;
		}
		else if ((lhs.rows == rhs.rows) && (lhs.columns == rhs.columns)) {

			for (int i = 0; i < lhs.rows; i++) {
				for (int j = 0; j < lhs.columns; j++) {
					if (lhs.matrix[i][j] != rhs.matrix[i][j]) {
						return false;
					}
				}
			}
			return true;
		}
		return false;
	}

	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {

		if ((lhs.GetNumRows() == 0 || lhs.GetNumColumns() == 0)
			&&
			(rhs.GetNumRows() == 0 || rhs.GetNumColumns() == 0)
			) {
			return Matrix();
		}
		else if ((lhs.rows == rhs.rows) && (lhs.columns == rhs.columns)) {
			Matrix result(lhs.rows, lhs.columns);

			for (int i = 0; i < lhs.rows; i++) {
				for (int j = 0; j < lhs.columns; j++) {
					result.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
				}
			}

			return result;
		}
		else {
			throw std::invalid_argument("invalid argument");
		}
	}
};