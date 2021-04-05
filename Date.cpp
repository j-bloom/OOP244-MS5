/****************************
* Name: Jaron Bloom
* Email: jbloom5@myseneca.ca
* Section: C
****************************/

// Final Project Milestone 1
//
// Version 1.0
// Date
// Author
// Description
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name Jaron Bloom       Date July 11/18               Reason
/////////////////////////////////////////////////////////////////
#include "Date.h"
#include <iomanip>
using namespace std;

namespace AMA {

	Date::Date() {
		_year = 0;
		_month = 0;
		_day = 0;
		_comp = 0;
		_error = 0;
	}

	Date::Date(int year, int month, int day) {
		*this = Date();
		if (!(year >= min_year && year <= max_year)) {
			errCode(YEAR_ERROR);
		}
		else if (!(month >= 1 && month <= 12)) {
			errCode(MON_ERROR);
		}
		else if (!(day >= 1 && day <= mdays(month, year))) {
			errCode(DAY_ERROR);
		}
		else {
			_year = year;
			_month = month;
			_day = day;
			_comp = year * 372 + month * 13 + day;
			errCode(NO_ERROR);
		}

	}

	void Date::errCode(int errorCode) {
		if (errorCode == 0) {
			_error = NO_ERROR;
		}
		else if (errorCode == 1) {
			_error = CIN_FAILED;
		}
		else if (errorCode == 2) {
			_error = YEAR_ERROR;
		}
		else if (errorCode == 3) {
			_error = MON_ERROR;
		}
		else if (errorCode == 4) {
			_error = DAY_ERROR;
		}
	}

	int Date::errCode() const {
		return _error;
	}

	// number of days in month mon_ and year year_
	//
	int Date::mdays(int mon, int year)const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	bool Date::isEmpty() const {
		if (_year == 0 && _month == 0 && _day == 0 && _comp == 0 && _error == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	bool Date::operator==(const Date& rhs) const {
		return (!((*this).isEmpty() && rhs.isEmpty()) && _comp && _comp ? true : false);
	}

	bool Date::operator!=(const Date& rhs) const {
		return (!((*this).isEmpty() && rhs.isEmpty()) && _comp && _comp ? true : false);
	}

	bool Date::operator<(const Date& rhs) const {
		return (!((*this).isEmpty() && rhs.isEmpty()) && _comp && _comp ? true : false);
	}

	bool Date::operator>(const Date& rhs) const {
		return (!((*this).isEmpty() && rhs.isEmpty()) && _comp && _comp ? true : false);
	}

	bool Date::operator<=(const Date& rhs) const {
		return (!((*this).isEmpty() && rhs.isEmpty()) && _comp && _comp ? true : false);
	}

	bool Date::operator>=(const Date& rhs) const {
		return (!((*this).isEmpty() && rhs.isEmpty()) && _comp && _comp ? true : false);
	}

	bool Date::bad() const {
		if (_error != NO_ERROR) {
			return true;
		}
		else {
			return false;
		}
	}

	void Date::read(std::istream& is) {
		int year, month, day;
		char x = '/';
		is >> year >> x >> month >> x >> day;
		if (year == 0 || month == 0 || day == 0) {
			return	errCode(CIN_FAILED);
		}
		else if (!((year <= max_year) && (year >= min_year))) {
			return errCode(YEAR_ERROR);
		}
		else if (!((month >= 1) && (month <= 12))) {
			return errCode(MON_ERROR);
		}
		else if (!((day >= 1) && (day <= mdays(month, year)))) {
			return errCode(DAY_ERROR);
		}
		else {
			_year = year;
			_month = month;
			_day = day;
			errCode(NO_ERROR);
		}
	}

	void Date::write(std::ostream& os) const {
		char x = '/';
		os << setfill('0') << _year << x << setw(2) << _month << x << setw(2) << _day;
	}

	std::istream& operator>>(std::istream& is, Date& istr) {
		istr.read(is);
		return is;
	}

	std::ostream& operator<<(std::ostream& os, const Date& ostr) {
		ostr.write(os);
		return os;
	}
}
