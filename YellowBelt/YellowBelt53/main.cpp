#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <memory>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual float Perimeter() const = 0;
    virtual float Area() const = 0;
};

class Triangle : public Figure {
    const float a;
    const float b;
    const float c;
public:
    Triangle(const float _a, const float _b, const float _c) : a(_a), b(_b), c(_c) {};
    string Name() const override {
        return "TRIANGLE";
    }
    float Perimeter() const override {
        return a + b + c;
    }
    float Area() const override {
        float p = Perimeter() / 2;
        return float(sqrt(p * (p - a) * (p - b) * (p - c)));
    }
};

class Rect : public Figure {
    const float width;
    const float height;
public:
    Rect(const float _width, const float _height) : width(_width), height(_height) {};
    string Name() const override {
        return "RECT";
    }
    float Perimeter() const override {
        return 2 * (width + height);
    }
    float Area() const override {
        return width * height;
    }
};

class Circle : public Figure {
    const float r;
public:
    Circle(const float _r) : r(_r) {};
    string Name() const override {
        return "CIRCLE";
    }
    float Perimeter() const override {
        return float(2 * 3.14 * r);
    }
    float Area() const override {
        return float(3.14 * r * r);
    }
};

shared_ptr<Figure> CreateFigure(istringstream& is) {

    string figType;
    is >> figType;

    if (figType == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b ,c);
    }
    else if (figType == "RECT") {
        int w, h;
        is >> w >> h;
        return make_shared<Rect>(w, h);
    }
    else {
        int r;
        is >> r;
        return make_shared<Circle>(r);
    }
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}