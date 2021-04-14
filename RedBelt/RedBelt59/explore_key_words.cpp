#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <thread>
#include <future>
#include <vector>
#include <set>
#include <string_view>

#include "../test_runner.h"
#include "../profiler.h"

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

struct Stats {
    map<string, int> word_frequences;
    void operator += (const Stats& other) {
        for (const pair<string, int>& mapPair : other.word_frequences) {
            word_frequences[mapPair.first] += mapPair.second;
        }
    }
    void operator += (const Stats&& other) {
        for (const pair<string, int>& mapPair : other.word_frequences) {
            word_frequences[mapPair.first] += mapPair.second;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    size_t curPos = 0, spacePos;
    while (curPos < line.length()) {
        spacePos = line.find_first_of(' ', curPos);

        auto findIter = key_words.find(line.substr(curPos, spacePos - curPos));
        if (findIter != key_words.end()) {
            result.word_frequences[*findIter]++;
        }

        if (spacePos == line.npos) {
            break;
        }
        curPos = spacePos + 1;
    }

    return result;
}

Stats ExploreKeyWordsSingleThread(const set<string>& key_words, const IteratorRange<vector<string>::iterator> &range) {
    Stats result;

    for (const string &line : range) {
        result += move(ExploreLine(key_words, line));
    }

    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {

    int threadsNb = 4;//  thread::hardware_concurrency();
    vector<string> inputLines;

    for (string line; getline(input, line); ) {
        inputLines.push_back(line);
    }

    vector<future<Stats>> futures;
    for (auto stringBlock : Paginate(inputLines, inputLines.size() / threadsNb)) {
        futures.push_back(async(ExploreKeyWordsSingleThread, ref(key_words), stringBlock));
    }

    Stats result;
    for (future<Stats> &fut : futures) {
        result += move(fut.get());
    }

    return result;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
    
    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
    
    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
      {"yangle", 6},
      {"rocks", 2},
      {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
