/*	���������� �����, �������������� ����� ����� � ��������������� �������. 
	����� ������ ��������� ��� ��������� ������:
		class SortedStrings {
		public:
		  void AddString(const string& s) {
		    // �������� ������ s � �����
		  }
		  vector<string> GetSortedStrings() {
		    // �������� ����� �� ���� ����������� ����� � ��������������� �������
		  }
		private:
		  // ��������� ����
		}; */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class SortedStrings {
	vector<string> _vec;
public:
	void AddString(const string& s) {
		_vec.push_back(s);
	}
	vector<string> GetSortedStrings() {
		sort(_vec.begin(), _vec.end());
		return _vec;
	}
};