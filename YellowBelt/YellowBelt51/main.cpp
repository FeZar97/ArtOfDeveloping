#include <iostream>

using namespace std;

class Animal {
public:
    Animal(const string newName) : Name(newName) {
    }
    const string Name;
};


class Dog: public Animal {
public:
    Dog(const string newName) : Animal(newName) {
    }

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};