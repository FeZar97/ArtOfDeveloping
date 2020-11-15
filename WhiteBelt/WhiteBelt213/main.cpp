/* Реализуйте систему хранения автобусных маршрутов. Вам нужно обрабатывать следующие запросы:
	NEW_BUS bus stop_count stop1 stop2 ... — добавить маршрут автобуса с названием bus и stop_count остановками с названиями stop1, stop2, ...
	BUSES_FOR_STOP stop — вывести названия всех маршрутов автобуса, проходящих через остановку stop.
	STOPS_FOR_BUS bus — вывести названия всех остановок маршрута bus со списком автобусов, на которые можно пересесть на каждой из остановок.
	ALL_BUSES — вывести список всех маршрутов с остановками.

Формат ввода
	В первой строке ввода содержится количество запросов Q, затем в Q строках следуют описания запросов.
	Гарантируется, что все названия маршрутов и остановок состоят лишь из латинских букв, цифр и знаков подчёркивания.
	Для каждого запроса NEW_BUS bus stop_count stop1 stop2 ... гарантируется, что маршрут bus отсутствует, 
		количество остановок больше 0, а после числа stop_count следует именно такое количество названий остановок, 
		причём все названия в каждом списке различны.

Формат вывода
	Для каждого запроса, кроме NEW_BUS, выведите соответствующий ответ на него:
	- На запрос BUSES_FOR_STOP stop выведите через пробел список автобусов, проезжающих через эту остановку, 
	  в том порядке, в котором они создавались командами NEW_BUS.
	  Если остановка stop не существует, выведите No stop.

	- На запрос STOPS_FOR_BUS bus выведите описания остановок маршрута bus в отдельных строках в том порядке, 
	  в котором они были заданы в соответствующей команде NEW_BUS. Описание каждой остановки stop должно 
	  иметь вид Stop stop: bus1 bus2 ..., где bus1 bus2 ... — список автобусов, проезжающих через остановку stop, 
	  в порядке, в котором они создавались командами NEW_BUS, за исключением исходного маршрута bus. Если через 
	  остановку stop не проезжает ни один автобус, кроме bus, вместо списка автобусов для неё выведите no interchange. 
	  Если маршрут bus не существует, выведите No bus.

	- На запрос ALL_BUSES выведите описания всех автобусов в алфавитном порядке. Описание каждого маршрута bus должно 
	  иметь вид Bus bus: stop1 stop2 ..., где stop1 stop2 ... — список остановок автобуса bus в порядке, 
	  в котором они были заданы в соответствующей команде NEW_BUS. 
	  Если автобусы отсутствуют, выведите No buses.

	Предупреждение
	Условие задачи выше содержит много важных деталей. Если вы не уверены в том, что не упустили ни одной, перечитайте условие ещё раз.
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