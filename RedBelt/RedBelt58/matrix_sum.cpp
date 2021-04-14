#include <vector>
#include <thread>
#include <future>
#include <numeric>

#include "../test_runner.h"

using namespace std;

template <typename Iterator>
class IteratorRange {
    Iterator first, last;

public:
    IteratorRange(Iterator f, Iterator l) : first(f), last(l) {
    }

    Iterator begin() const {
        return first;
    }

    Iterator end() const {
        return last;
    }

    size_t size() const {
        return last - first;
    }
};

template <typename Iterator>
auto MakeRange(Iterator begin, Iterator end) {
    return IteratorRange<Iterator>(begin, end);
}

template <typename Iterator>
class Paginator {

    std::vector<IteratorRange<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        pages.clear();

        for (Iterator start = begin; start < end;) {
            size_t rangeLength = ((end - start) < page_size ? (end - start) : page_size);
            IteratorRange<Iterator> nextRange = MakeRange<Iterator>(start, start + rangeLength);
            pages.push_back(nextRange);

            if (rangeLength == page_size) {
                start += page_size;
            }
            else {
                break;
            }
        }
    }

    auto begin() const {
        return pages.begin();
    }

    auto end() const {
        return pages.end();
    }

    size_t size() const {
        return pages.size();
    }
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
    int64_t result = 0;

    int threadsNb = std::thread::hardware_concurrency();
    int rowsPerThread = matrix.size() / threadsNb + 1;

    vector<future<int64_t>> futures;

    for (auto rowsBlock : Paginate(matrix, rowsPerThread)) {
        futures.push_back(async([rowsBlock]() {
            int64_t blockSum = 0;
            for (auto row : rowsBlock) {
                blockSum += accumulate(row.begin(), row.end(), 0);
            }
            return blockSum;
        })); 
    }

    for (auto &fut : futures) {
        result += fut.get();
    }

    return result;
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
