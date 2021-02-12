/*	�������
	� ���� ������ ��� ���� ����������� ����� Matrix ��� ������������� ������������� �������. ����� ��������, ����� Matrix ������ �����:
	- ����������� �� ���������, ������� ������ ������� � ���� ����� � ���� ��������
	- ����������� �� ���� ������������� ����������: num_rows � num_cols, � ������� ������ ���������� ����� � �������� ������� ��������������
	- ����� Reset, ����������� ��� ������������� ���������, ������� ������ ����� ���������� ����� � �������� ������� ��������������;
	  ����� Reset ������ ������� ������� �� �������� � �������� ��� � ��������
	- ����������� ����� At, ������� ��������� ����� ������ � ����� �������
	  (������ � ���� �������; ��������� ����� � �������� ���������� � ����)
	  � ���������� �������� � �������������� ������ �������
	- ������������� ����� At � ������ �� �����������, �� ������������ ������ �� �������� � �������������� ������ �������
	- ����������� ������ GetNumRows � GetNumColumns, ������� ���������� ���������� ����� � �������� ������� ��������������

	���� ���������� ����� ��� ���������� ��������, ���������� � ����������� ������ Matrix ��� ����� Reset,
	��������� �������������, �� ������ ���� ��������� ����������� ���������� out_of_range.

	��� �� ���������� ������ ������� ����� At, ���� ���������� � ���� ������ ������� �� ������� �������.

	����� ����, ��� ������ Matrix ������ ���� ���������� ��������� ���������:
	- �������� ����� �� ������ istream; ������ ����� ������� � ������� ������� ���������� ����� � ��������
	  (������ � ���� �������), � ����� ��� �������� �������: ������� ������� ������ ������ � ������� �������,
	  ����� ������� ������ ������ � ������� ������� � ��� �����
	- �������� ������ � ����� ostream; �� ������ �������� ������� � ��� �� �������, � ����� � ������ ��������
	  �����, � � ������ ������ ���������� ����� � ��������, �� ������ � �������� ������ ������, � ������� � �������� ������ ������ � �.�.
	- �������� �������� �� ��������� (==): �� ������ ���������� true, ���� ������������ ������� ����� ���������� ������
	  � ��� �� ��������������� �������� ����� ����� �����, � ��������� ������ �� ������ ���������� false.
	- �������� ��������: �� ������ ��������� ��� ������� � ���������� ����� �������, ������� �������� �� ������;
	  ���� ���������� ������� ����� ������ ������� ���� �������� ������ ����������� ����������� ���������� invalid_argument.

	��� ���� ��������� �������, � ����� ������ ����� � ������.
	����� �� ���������� ����� Matrix, �� ������ ������������ ���� ������, ����� ���������, ��� ��� ��� �������� ���������. */
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