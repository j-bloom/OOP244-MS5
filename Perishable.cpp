/****************************
* Name: Jaron Bloom
* Email: jbloom5@myseneca.ca
* Section: C
****************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Perishable.h"

using namespace std;
namespace AMA {
	// calling the base constructor and setting type to "P"
	Perishable::Perishable() : Product('P') {}

	/*std::fstream& Perishable::store(std::fstream& file) const {
		return store(file, true);
	}*/

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const {
		Product::store(file, false);
		file << ',' << Expiry;
		if (newLine) {
			file << std::endl;
		}
		return file;
	}

	std::fstream& Perishable::load(std::fstream& file) {
		Product::load(file);
		file.ignore();
		Expiry.read(file);
		return file;
	}

	//Writes the output and checks for Safe Empty State
	std::ostream& Perishable::write(std::ostream& os, bool linear) const {
		Product::write(os, linear);
		if (isClear()) {
			if (!linear) {
				os << "\n Expiry date: ";
			}
			Expiry.write(os);
		}
		return os;
	}

	//Checks and sets the Error State
	std::istream& Perishable::read(std::istream& is) {
		Product::read(is); //Prompt Parent Class's other stuff first
		if (isClear()) { //if read didn't have errors prompt for date
			cout << " Expiry date (YYYY/MM/DD): ";
			Expiry.read(is); //load date object with user input
			if (Expiry.errCode() == CIN_FAILED) {
				message("Invlaid Date Entry");
			}

			if (Expiry.errCode() == YEAR_ERROR) {
				message("Invalid Year in Date Entry");
			}

			if (Expiry.errCode() == MON_ERROR) {
				message("Invalid Month in Date Entry");
			}

			if (Expiry.errCode() == DAY_ERROR) {
				message("Invalid Day in Date Entry");
			}
			if (Expiry.errCode() != NO_ERROR) {
				is.istream::setstate(std::ios::failbit);
			}
		}
		return is;
	}

	const Date& Perishable::expiry() const {
		return Expiry;
	}
}
