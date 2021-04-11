#include "stats.h"

Stats::Stats() {
	for (const string& method : AvailableMethods) {
		methodStats.insert(make_pair<string_view, int>(method, 0));
	}
	for (const string& uri : AvailableUris) {
		uriStats.insert(make_pair<string_view, int>(uri, 0));
	}
}

void Stats::AddMethod(string_view method) {
	for (const string_view availMethod : AvailableMethods) {
		if (method.compare(availMethod) == 0) {
			methodStats[availMethod]++;
			return;
		}
	}
	methodStats[AvailableMethods.back()]++;
}

void Stats::AddUri(string_view uri) {
	for (const string_view availUri : AvailableUris) {
		if (uri.compare(availUri) == 0) {
			uriStats[availUri]++;
			return;
		}
	}
	uriStats[AvailableUris.back()]++;
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return methodStats;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uriStats;
}

HttpRequest ParseRequest(string_view line) {
	HttpRequest result;

	vector<string_view> fields(3);
	size_t curPos = line.find_first_not_of(' '), curFieldIdx = 0;
	const size_t strEnd = line.npos;

	while (true) {
		size_t nextSpacePos = line.find(' ', curPos);
		if (nextSpacePos == strEnd) {
			fields[curFieldIdx++] = line.substr(curPos);
			break;
		}
		else {
			fields[curFieldIdx++] = line.substr(curPos, nextSpacePos - curPos);
			curPos = nextSpacePos + 1;
		}
	}

	result = { fields[0], fields[1], fields[2] };

	return result;
}
