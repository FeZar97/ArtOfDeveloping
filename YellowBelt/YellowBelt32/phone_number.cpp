#include <stdexcept>
#include "phone_number.h"

PhoneNumber::PhoneNumber(const string& international_number) {

	if (international_number.empty()) {
		throw invalid_argument("empty string");
	}

	if (international_number[0] != '+') {
		throw invalid_argument("not started with plus");
	}

	country_code_ = "";
	city_code_ = "";
	local_number_ = "";

	int minusCnt{ 0 }, curSymIdx{ 1 };
	char curSym;
	string curPart = "";

	while (curSymIdx < international_number.length()) {

		curSym = international_number[curSymIdx];

		if (curSym != '-' || (curSym == '-' && minusCnt > 1) ) {
			curPart += curSym;
		}
		else {

			if (minusCnt == 0) {
				country_code_ = curPart;
			}
			if (minusCnt == 1) {
				city_code_ = curPart;
			}
			curPart = "";
			minusCnt++;
		}

		curSymIdx++;
	}
	local_number_ = curPart;

	if (minusCnt < 2) {
		throw invalid_argument("too many minus");
	}

	if (country_code_.empty()) {
		throw invalid_argument("country_code is empty");
	}

	if (city_code_.empty()) {
		throw invalid_argument("city_code is empty");
	}

	if (local_number_.empty()) {
		throw invalid_argument("local_number is empty");
	}
}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return "+" + GetCountryCode() + "-" + GetCityCode() + "-" + GetLocalNumber();
}
