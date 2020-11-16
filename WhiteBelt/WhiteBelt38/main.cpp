/*	Определите тип Incognizable, для которого следующий код будет корректен:	
	int main() {
	  Incognizable a;
	  Incognizable b = {};
	  Incognizable c = {0};
	  Incognizable d = {0, 1};
	  return 0;
	} */

class Incognizable {
public:
	Incognizable(int a = 0, int b = 0) {};
};