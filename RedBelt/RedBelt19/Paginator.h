#pragma once

#include <vector>

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