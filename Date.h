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
// Name: Jaron Bloom          Date: July 11/18             Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>
#include "ErrorState.h"

//#define NO_ERROR 0
//#define CIN_FAILED 1
//#define YEAR_ERROR 2
//#define MON_ERROR 3
//#define DAY_ERROR 4

namespace AMA {
	const int min_year = 2000;
	const int max_year = 2030;
	const int NO_ERROR = 0;
	const int CIN_FAILED = 1;
	const int YEAR_ERROR = 2;
	const int MON_ERROR = 3;
	const int DAY_ERROR = 4;

	class Date {
		int _year;
		int _month;
		int _day;
		int _comp;
		int _error;
		int mdays(int, int) const;
		void errCode(int);

	public:
		Date();
		Date(int, int, int);

		bool isEmpty() const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		int errCode() const;
		bool bad() const;
		void read(std::istream&);
		void write(std::ostream&) const;

	};

	std::istream& operator>>(std::istream& is, Date& istr);
	std::ostream& operator<<(std::ostream& os, const Date& ostr);




}
#endif
