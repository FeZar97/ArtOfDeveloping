#include <vector>

#include "../test_runner.h"

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> result;
    Sentence<Token> curSentence;

    int curTokenIdx = 0;
    bool isEnd = false, isPrevEnd = false;

    while (curTokenIdx < tokens.size()) {

        isPrevEnd = isEnd;
        isEnd = tokens[curTokenIdx].IsEndSentencePunctuation();

        if (!isEnd && isPrevEnd) {
            result.push_back(move(curSentence));
        }
        curSentence.push_back(move(tokens[curTokenIdx++]));
    }

    if (curSentence.size()) {
        result.push_back(move(curSentence));
    }

    return result;
}

struct TestToken {
  string data;
  bool is_end_sentence_punctuation = false;

  bool IsEndSentencePunctuation() const {
    return is_end_sentence_punctuation;
  }
  bool operator==(const TestToken& other) const {
    return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
  }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
  return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void Test1() {
    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!"} })),
        vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!"}}
            })
    );
}

void Test2() {
    ASSERT_EQUAL(
        SplitIntoSentences(vector<TestToken>({ {"Split"}, {"into"}, {"sentences"}, {"!", true} })),
        vector<Sentence<TestToken>>({
            {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
            })
    );
}

void Test3() {
    ASSERT_EQUAL(
      SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
      vector<Sentence<TestToken>>({
          {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
          {{"Without"}, {"copies"}, {".", true}},
      })
    );
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, Test1);
  RUN_TEST(tr, Test2);
  RUN_TEST(tr, Test3);
  return 0;
}
