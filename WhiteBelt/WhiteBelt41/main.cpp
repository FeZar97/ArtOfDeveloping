/*	Дана структура LectureTitle:

		struct LectureTitle {
		  string specialization;
		  string course;
		  string week;
		};

	Допишите конструктор и структуры Specialization, Course, Week так, чтобы объект LectureTitle можно было создать с помощью кода
		LectureTitle title(
			Specialization("C++"),
			Course("White belt"),
			Week("4th")
		);

	но нельзя было с помощью следующих фрагментов кода:

		LectureTitle title("C++", "White belt", "4th");
		LectureTitle title(string("C++"), string("White belt"), string("4th"));
		LectureTitle title = {"C++", "White belt", "4th"};
		LectureTitle title = {{"C++"}, {"White belt"}, {"4th"}};
		LectureTitle title(
			Course("White belt"),
			Specialization("C++"),
			Week("4th")
		);
		LectureTitle title(
			Specialization("C++"),
			Week("4th"),
			Course("White belt")
		); */
#include <string>

using namespace std;

struct Specialization {
	string s;
	explicit Specialization(string _s) :s(_s) {};
};

struct Course {
	string c;
	explicit Course(string _c) :c(_c) {};
};

struct Week {
	string w;
	explicit Week(string _w) :w(_w) {};
};

struct LectureTitle {
	string specialization;
	string course;
	string week;

	explicit LectureTitle(Specialization s, Course c, Week w): specialization(s.s), course(c.c), week(w.w) {}
};