/*	��� ���� ������� string AskTimeServer(), ��� ������� �������� ���������:
	- � �������� ����� ������ ��� ���������� �� ���� � ��������� �������, ���������� ������� �����;
	- ���� ��������� � ������� ������ �������, ������� ���������� ������� ����� � ���� ������;
	- ���� � �������� ��������� � ������� �������� ������� ��������, ������� ����������� ���������� system_error;
	- ������� ����� ����������� ������ ����������, ����� �������� � ������ ���������.

	��������� ������� AskTimeServer, �������� ����� TimeServer �� ��������� �����������:
		class TimeServer {
		public:
		  string GetCurrentTime();
		private:
		  string last_fetched_time = "00:00:00";
		};
		
	����� GetCurrentTime ������ ����� ���� ���:
	- �� ������ ������� ������� AskTimeServer, �������� � ��������� � ���� last_fetched_time � ������� �������� ����� ����;
	- ���� AskTimeServer ��������� ���������� system_error, ����� GetCurrentTime ������ ��� ������� � ������� ������� �������� ���� last_fetched_time. 
	  ����� ������� �� �������� �� ������������ ������� ��������, ��������� ��������, ������� ���� �������� ��� ��������� �������� ��������� � �������;
	- ���� AskTimeServer ��������� ������ ����������, ����� GetCurrentTime ������ ���������� ��� ������, ������ ��� � ������ ������ TimeServer �� �� �����, 
	  ��� ������������ ��������, �� ��������� �� ������ ����.

	��� ��������� �������
	��� ��� ����, ���������� ��������� ������ TimeServer. � �� ��� ���� ����������� ����� GetCurrentTime ���, 
	��� ������� ����. ���� �������� ������ ������� AskTimeServer. ��� ������������ ����� ���������� �� ������ 
	��������� ��������� ������ ������� � � ����:
	- ������� ������;
	- ������ ���������� system_error (����� system_error ��������� � ������������ �������� ���� error_code, 
	  ������� ����� ������� ������ ��������� ��� ���������� � throw system_error(error_code());, 
	  ��������� ��. https://en.cppreference.com/w/cpp/error/system_error );
	- ������ ������ ����������. */
#include <iostream>
#include <exception>
#include <string>

using namespace std;

// string AskTimeServer() {
// 	// throw(system_error(error_code()));
// 	throw(invalid_argument(""));
// 	// return "12:34:56";
// }

class TimeServer {
	string last_fetched_time = "00:00:00";

public:
	string GetCurrentTime() {
		try {
			last_fetched_time = AskTimeServer();
		}
		catch (const system_error &se) {
		}
		return last_fetched_time;
	}
};

int main() {
	TimeServer ts;
	try {
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception& e) {
		cout << "Exception got: " << e.what() << endl;
	}

	return 0;
}