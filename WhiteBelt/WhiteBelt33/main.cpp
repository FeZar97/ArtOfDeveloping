/*	–еализуйте класс, поддерживающий набор строк в отсортированном пор€дке. 
	 ласс должен содержать два публичных метода:
		class SortedStrings {
		public:
		  void AddString(const string& s) {
		    // добавить строку s в набор
		  }
		  vector<string> GetSortedStrings() {
		    // получить набор из всех добавленных строк в отсортированном пор€дке
		  }
		private:
		  // приватные пол€
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