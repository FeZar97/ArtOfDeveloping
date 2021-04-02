#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        size_t curSize = dict.size();
        for (const auto& word : words) {
            dict.insert(word);
        }
        return dict.size() - curSize;
    }

    vector<string> KnownWords() {
        vector<string> result;
        result.assign(dict.begin(), dict.end());
        return result;
    }
};