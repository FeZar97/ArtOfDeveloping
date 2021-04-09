#include <string>
#include <set>
#include <vector>
#include <utility>
#include <map>
#include <string_view>

// #include "../test_runner.h"

using namespace std;

class Translator {

	set<string> language1words;
	set<string> language2words;
	map<string_view, string_view> forwardTranslator;
	map<string_view, string_view> backwardTranslator;

public:
	void Add(string_view source, string_view target) {
		auto insertPair1 = language1words.insert(string(source));
		auto insertPair2 = language2words.insert(string(target));
		forwardTranslator[*insertPair1.first] = *insertPair2.first;
		backwardTranslator[*insertPair2.first] = *insertPair1.first;
	}

	string_view TranslateForward(string_view source) const {
		auto wordIt = language1words.find(string(source));
		if (wordIt != language1words.end()) {
			return forwardTranslator.at(*wordIt);
		}
		else {
			return "";
		}
	}
	string_view TranslateBackward(string_view target) const {
		auto wordIt = language2words.find(string(target));
		if (wordIt != language2words.end()) {
			return backwardTranslator.at(*wordIt);
		}
		else {
			return "";
		}
	}
};

/*
void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));
	
	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}
 */
