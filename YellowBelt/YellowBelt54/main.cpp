#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
protected:
    const string profession;
    const string name;
public:
    Human(const string& _profession, const string& _name)
        : profession(_profession), name(_name) {}

    string Name() const {
        return name;
    }
    string Profession() const {
        return profession;
    }
    string nameWithProf() const {
        return profession + " " + name;
    }
    virtual void Walk(const string& destination) const {
        cout << nameWithProf() << " walks to: " << destination << endl;
    }
    virtual ~Human() = default;
};

void VisitPlaces(const Human& h, const vector<string>& places) {
    for (const auto& p : places) {
        h.Walk(p);
    }
}

class Student : public Human {
    const string FavouriteSong;
public:
    Student(const string& name, const string& favouriteSong) 
        : Human("Student", name), FavouriteSong(favouriteSong) {
    }
    void Learn() const {
        cout << nameWithProf() << " learns" << endl;
    }
    void SingSong() const {
        cout << nameWithProf() << " sings a song: " << FavouriteSong << endl;
    }
    void Walk(const string& destination) const override {
        Human::Walk(destination);
        SingSong();
    }
};

class Teacher : public Human {
    const string Subject;
public:
    Teacher(const string& name, const string& subject) 
        : Human("Teacher", name), Subject(subject) {
    }
    void Teach() const {
        cout << nameWithProf() << " teaches: " << Subject << endl;
    }
};

class Policeman : public Human {
public:
    Policeman(const string& name)
        : Human("Policeman", name) {
    }
    void Check(const Human& h) const {
        cout << nameWithProf() << " checks " << h.Profession() << ". "
            << h.Profession() << "'s name is: " << h.Name() << endl;
    }
};

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}