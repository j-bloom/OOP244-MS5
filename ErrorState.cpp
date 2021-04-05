/***************************
Name: Jaron Bloom
Email: jbloom5@myseneca.ca
Section: C
**************************/

#include <iostream>
#include <cstring>
#include "ErrorState.h"
using namespace std;
namespace AMA {
	//Creating ErrorState
	ErrorState::ErrorState(const char* errorMessage) {
		mess = nullptr;
		if (errorMessage != nullptr) {
			message(errorMessage);
		}
	}

	//Destructor
	ErrorState::~ErrorState() {
		clear();
	}

	//Clearing ErrorState
	void ErrorState::clear() {
		delete[] mess;
		mess = nullptr;
	}

	// Query if clear
	bool ErrorState::isClear() const {
		if (mess == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	//Copying the ErrorState
	void ErrorState::message(const char* str) {
		delete[] mess;
		mess = new char[strlen(str) + 1];
		strcpy(mess, str);
	}

	//Returning ErrorState message
	const char* ErrorState::message() const {
		return mess;
	}

	//Output
	std::ostream& operator<< (std::ostream& os, const ErrorState& eS) {
		if (!eS.isClear()) {
			os << eS.message();
		}
		return os;
	}
}