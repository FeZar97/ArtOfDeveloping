#include <vector>
#include <utility>

#include "../test_runner.h"

using namespace std;

using namespace std;

template<typename T>
class Table {

	vector<vector<T>> table;

public:
	Table(size_t rowNb, size_t colNb) {
		Resize(rowNb, colNb);
	}

	vector<T>& operator[](int rowIdx) {
		return table[rowIdx];
	}

	vector<T>& operator[](int rowIdx) const {
		return table[rowIdx];
	}

	void Resize(size_t rowNb, size_t colNb) {
		table.resize(rowNb);
		for (auto& row : table) {
			row.resize(colNb);
		}
	}

	pair<size_t, size_t> Size() const {
		pair<size_t, size_t> result{ 0, 0 };

		if (table.empty()) {
			return result;
		}

		if (table.at(0).empty()) {
			return result;
		}

		result = { table.size(), table.at(0).size() };
		return result;
	}
};

void TestTable() {
	Table<int> t(1, 1);
	ASSERT_EQUAL(t.Size().first, 1u);
	ASSERT_EQUAL(t.Size().second, 1u);
	t[0][0] = 42;
	ASSERT_EQUAL(t[0][0], 42);
	t.Resize(3, 4);
	ASSERT_EQUAL(t.Size().first, 3u);
	ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}