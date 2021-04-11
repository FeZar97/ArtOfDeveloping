#pragma once

#include <string_view>
#include <array>
#include <map>
#include <vector>

#include "http_request.h"

using namespace std;

const static array<string, 5> AvailableMethods = { "GET", "POST", "PUT", "DELETE", "UNKNOWN" };
const static array<string, 6> AvailableUris = { "/", "/order", "/product", "/basket", "/help", "unknown" };

class Stats {

	map<string_view, int> methodStats;
	map<string_view, int> uriStats;

public:
	Stats();
	void AddMethod(string_view method);
	void AddUri(string_view uri);
	const map<string_view, int>& GetMethodStats() const;
	const map<string_view, int>& GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);
