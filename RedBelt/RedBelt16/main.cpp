/*
#include <string>
#include <vector>
using namespace std;
*/

#define CONCAT_NX(a,b) a##b
#define CONCAT(a,b) CONCAT_NX(a,b)
#define UNIQ_ID CONCAT(uniqueVariable, __LINE__)

/*
int main() {
	int UNIQ_ID = 0;
	string UNIQ_ID = "hello";
	vector<string> UNIQ_ID = { "hello", "world" };
	vector<int> UNIQ_ID = { 1, 2, 3, 4 };
}
*/