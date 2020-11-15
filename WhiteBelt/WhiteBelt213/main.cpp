/* ���������� ������� �������� ���������� ���������. ��� ����� ������������ ��������� �������:
	NEW_BUS bus stop_count stop1 stop2 ... � �������� ������� �������� � ��������� bus � stop_count ����������� � ���������� stop1, stop2, ...
	BUSES_FOR_STOP stop � ������� �������� ���� ��������� ��������, ���������� ����� ��������� stop.
	STOPS_FOR_BUS bus � ������� �������� ���� ��������� �������� bus �� ������� ���������, �� ������� ����� ��������� �� ������ �� ���������.
	ALL_BUSES � ������� ������ ���� ��������� � �����������.

������ �����
	� ������ ������ ����� ���������� ���������� �������� Q, ����� � Q ������� ������� �������� ��������.
	�������������, ��� ��� �������� ��������� � ��������� ������� ���� �� ��������� ����, ���� � ������ �������������.
	��� ������� ������� NEW_BUS bus stop_count stop1 stop2 ... �������������, ��� ������� bus �����������, 
		���������� ��������� ������ 0, � ����� ����� stop_count ������� ������ ����� ���������� �������� ���������, 
		������ ��� �������� � ������ ������ ��������.

������ ������
	��� ������� �������, ����� NEW_BUS, �������� ��������������� ����� �� ����:
	- �� ������ BUSES_FOR_STOP stop �������� ����� ������ ������ ���������, ����������� ����� ��� ���������, 
	  � ��� �������, � ������� ��� ����������� ��������� NEW_BUS.
	  ���� ��������� stop �� ����������, �������� No stop.

	- �� ������ STOPS_FOR_BUS bus �������� �������� ��������� �������� bus � ��������� ������� � ��� �������, 
	  � ������� ��� ���� ������ � ��������������� ������� NEW_BUS. �������� ������ ��������� stop ������ 
	  ����� ��� Stop stop: bus1 bus2 ..., ��� bus1 bus2 ... � ������ ���������, ����������� ����� ��������� stop, 
	  � �������, � ������� ��� ����������� ��������� NEW_BUS, �� ����������� ��������� �������� bus. ���� ����� 
	  ��������� stop �� ��������� �� ���� �������, ����� bus, ������ ������ ��������� ��� �� �������� no interchange. 
	  ���� ������� bus �� ����������, �������� No bus.

	- �� ������ ALL_BUSES �������� �������� ���� ��������� � ���������� �������. �������� ������� �������� bus ������ 
	  ����� ��� Bus bus: stop1 stop2 ..., ��� stop1 stop2 ... � ������ ��������� �������� bus � �������, 
	  � ������� ��� ���� ������ � ��������������� ������� NEW_BUS. 
	  ���� �������� �����������, �������� No buses.

	��������������
	������� ������ ���� �������� ����� ������ �������. ���� �� �� ������� � ���, ��� �� �������� �� �����, ����������� ������� ��� ���.
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class BusRoute {
	string _bName;
	vector<string> _stops;
public:
	BusRoute() {};
	BusRoute(const string &b) : _bName(b) {};
	~BusRoute() {};

	string name() {
		return _bName;
	}
	vector<string> stops() {
		return _stops;
	}

	bool existStop(const string &s) {
		for (auto _s : _stops) {
			if (_s == s) {
				return true;
			}
		}
		return false;
	};

	friend istream& operator>>(istream &is, BusRoute &_br) {
		int stopsNb;
		is >> _br._bName >> stopsNb;
		_br._stops.resize(stopsNb);
		for (int i = 0; i < stopsNb; i++) {
			is >> _br._stops[i];
		}
		return is;
	};
};

class Routes {
	vector<BusRoute> _routes;

public:
	Routes() {};
	~Routes() {};

	BusRoute* route(string &routeName) {
		for (auto &r : _routes) {
			if (r.name() == routeName) {
				return &r;
			}
		}
		return nullptr;
	};

	vector<BusRoute> routes() {
		return _routes;
	}

	void createNewRoute() {
		_routes.push_back({});
		cin >> _routes[_routes.size() - 1];
	}

	vector<string> busesForStop(const string &stopName) {
		vector<string> result;
		for (auto r: _routes) {
			if (r.existStop(stopName)) {
				result.push_back(r.name());
			}
		}
		return result;
	}

	bool empty() {
		return _routes.empty();
	}
};

void PrintSVector(const vector<string> &vec) {
	for (auto v : vec) {
		cout << v << " ";
	}
	cout << endl;
}

int main() {
	int queryNb;
	string command, busName, stopName;
	Routes routes;
	BusRoute tempBus;

	cin >> queryNb;

	for (int i = 0; i < queryNb; i++) {
		cin >> command;

		if (command == "NEW_BUS") {
			routes.createNewRoute();
		} 
		else if (command == "BUSES_FOR_STOP") {
			cin >> stopName;
			vector<string> answer = routes.busesForStop(stopName);
			if (answer.empty()) {
				cout << "No stop" << endl;
			} else {
				PrintSVector(answer);
			}
		}
		else if(command == "STOPS_FOR_BUS") {
			cin >> busName;
			BusRoute *currentRoute = routes.route(busName);
			if (currentRoute) {
				vector<string> busesForStop;
				for (auto stop : currentRoute->stops()) {
					busesForStop = routes.busesForStop(stop);
					cout << "Stop " << stop << ": ";
					if (busesForStop.size() <= 1) {
						cout << "no interchange" << endl;
					}
					else {
						for (auto b : busesForStop) {
							if (b != currentRoute->name()) {
								cout << b << " ";
							}
						}
						cout << endl;
					}
				}
			}
			else {
				cout << "No bus" << endl;
			}
		}
		else if (command == "ALL_BUSES") {
			if (routes.empty()) {
				cout << "No buses" << endl;
			}
			else {
				map<string, vector<string>> mapRoutes;
				for (auto r : routes.routes()) {
					mapRoutes.insert({ r.name(), r.stops() });
				}
				for (auto r : mapRoutes) {
					cout << "Bus " << r.first << ": ";
					PrintSVector(r.second);
				}
			}
		}
	}

	return 0;
}