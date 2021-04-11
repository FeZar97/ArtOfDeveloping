#include <string>
#include <list>

#include "../test_runner.h"

using namespace std;

class Editor {
    list<char> text;
    list<char>::iterator curPosIterator{ text.begin()};
    list<char> clipboard;

public:
    Editor() {};

    void Left() {
        if (curPosIterator != text.begin()) {
            curPosIterator--;
        }
    }

    void Right() {
        if (curPosIterator != text.end()) {
            curPosIterator++;
        }
    }

    void Insert(char token) {
        curPosIterator = ++text.insert(curPosIterator, token);
    }

    void Cut(size_t tokens = 1) {
        clipboard.clear();
        if(tokens) {
            auto startIt = curPosIterator;
            auto maxLength = distance(curPosIterator, text.end());
            auto cursorShift = min(tokens, size_t(maxLength));
            advance(curPosIterator, cursorShift);
            clipboard.splice(clipboard.begin(), text,
                startIt, curPosIterator);
        }
    }

    void Copy(size_t tokens = 1) {
        clipboard.clear();
        if (tokens) {
            auto startIt = curPosIterator;
            auto maxLength = distance(curPosIterator, text.end());
            auto cursorShift = min(tokens, size_t(maxLength));
            advance(curPosIterator, cursorShift);
            clipboard = { startIt, curPosIterator };
            curPosIterator = startIt;
        }
    }

    void Paste() {
        text.insert(curPosIterator, clipboard.begin(), clipboard.end());
    }

    string GetText() const {
        return { text.begin(), text.end() };
    }
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;
        
        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);
        
        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;
        
        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();
        
        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;
    
    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }
    
    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");
    
    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;
    
    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "example");
}

void LocalTest1() {
    Editor editor;

    editor.Paste();
    editor.Copy(0);
    editor.Cut(0);
    TypeText(editor, "example text");

    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();

    editor.Cut(100);

    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();

    editor.Paste();

    for (int i = 0; i < 100; i++) {
        editor.Right();
    }
    editor.Left();

    // cut space
    editor.Cut(1);

    for (int i = 0; i < 100; i++) {
        editor.Left();
    }
    editor.Right();
    editor.Right();
    editor.Right();
    editor.Right();

    // paste space
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "text example");
}

void LocalTest2() {
    Editor editor;

    editor.Paste();
    editor.Copy(0);
    editor.Cut(0);
    TypeText(editor, "example text");

    for (int i = 0; i < 4; i++) {
        editor.Left();
    }
    // state: "example |text"
    // clipboard state: ""

    editor.Cut(100);
    // text state: "example |"
    // clipboard state: "text"

    for (int i = 0; i < 8; i++) {
        editor.Left();
    }
    // text state: "|example "
    // clipboard state: "text"

    editor.Paste();
    // text state: "text|example "
    // clipboard state: "text"

    for (int i = 0; i < 100; i++) {
        editor.Right();
    }
    editor.Left();
    // text state: "textexample| "
    // clipboard state: "text"

    editor.Cut(1);
    // text state: "textexample|"
    // clipboard state: " "

    for (int i = 0; i < 100; i++) {
        editor.Left();
    }
    for (int i = 0; i < 4; i++) {
        editor.Right();
    }
    // text state: "text|example"
    // clipboard state: " "

    editor.Paste();
    // text state: "text |example"
    // clipboard state: " "

    ASSERT_EQUAL(editor.GetText(), "text example");


    for (int i = 0; i < 100; i++) {
        editor.Left();
    }
    // text state: "|text example"
    // clipboard state: " "

    editor.Cut(1000);
    // text state: "|"
    // clipboard state: "text example"

    // testing correctness of Left and Right in empty text
    for (int i = 0; i < 100; i++) {
        editor.Left();
    }
    for (int i = 0; i < 100; i++) {
        editor.Right();
    }

    editor.Paste();
    // text state: "text example|"
    // clipboard state: "text example"

    for (int i = 0; i < 100; i++) {
        editor.Left();
    }
    for (int i = 0; i < 100; i++) {
        editor.Right();
    }
    // text state: "text example|"
    // clipboard state: "text example"

    ASSERT_EQUAL(editor.GetText(), "text example");

    editor.Insert(' ');
    // text state: "text example |"
    // clipboard state: "text example"
    ASSERT_EQUAL(editor.GetText(), "text example ");

    editor.Paste();
    // text state: "text example text example|"
    // clipboard state: "text example"
    ASSERT_EQUAL(editor.GetText(), "text example text example");

    for (int i = 0; i < 7; i++) {
        editor.Left();
    }
    editor.Copy(7);
    // text state: "text example text |example"
    // clipboard state: "example"

    editor.Insert(' ');
    // text state: "text example text  |example"
    // clipboard state: "example"

    ASSERT_EQUAL(editor.GetText(), "text example text  example");

    editor.Copy(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "text example text  example");

    editor.Insert(' ');
    ASSERT_EQUAL(editor.GetText(), "text example text   example");

    editor.Copy(1);
    for (int i = 0; i < 1000; i++) {
        editor.Left();
    }
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "etext example text   example");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "eetext example text   example");

    editor.Insert(' ');
    ASSERT_EQUAL(editor.GetText(), "ee text example text   example");
}

void TestCopyPasteLastChars() {
    Editor editor;
    TypeText(editor, "happy birthday");
    editor.Left();
    editor.Left();
    editor.Copy(5);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "happy birthdayay");
}

void TestCut()
{
    Editor editor;
    //1
    editor.Cut(10);
    editor.Insert('a');
    editor.Left();
    //2
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    //3
    editor.Cut(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    TypeText(editor, "bcde");
    editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcde");
    editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
    //5
    editor.Cut(5);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    //6
    editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bcde");
    editor.Right();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bde");
    editor.Cut(1);
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy()
{
    Editor editor;
    //1
    editor.Copy(10);
    editor.Insert('a');
    editor.Paste();
    editor.Left();
    ASSERT_EQUAL(editor.GetText(), "a");
    //2
    editor.Copy(1);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");//between a
    //3
    editor.Copy(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");
    TypeText(editor, "bcde");
    editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left(); editor.Left();
    //4
    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcdea");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    RUN_TEST(tr, LocalTest1);
    RUN_TEST(tr, LocalTest2);
    RUN_TEST(tr, TestCopyPasteLastChars);
    RUN_TEST(tr, TestCut);
    RUN_TEST(tr, TestCopy);
    return 0;
}