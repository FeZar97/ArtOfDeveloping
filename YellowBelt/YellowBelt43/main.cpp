#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<string> SplitIntoWords(const string& s) {

    vector<string> words;

    auto prevSym = begin(s), curSym = begin(s);

    while (curSym != end(s) && prevSym != end(s)) {
        curSym = find(prevSym, end(s), ' ');

        words.push_back({ prevSym , curSym });

        prevSym = curSym;
        if (prevSym != end(s)) {
            prevSym++;
        }
    }

    return words;
}

// 4 С/Cpp/Java/Python

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}