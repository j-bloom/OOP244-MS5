/****************************
* Name: Jaron Bloom
* Email: jbloom5@myseneca.ca
* Section: C
****************************/

#ifndef Perishable_H
#define Perishable_H
#include <fstream>
#include <iostream>
#include "Date.h"
#include "Product.h"

namespace AMA {
	class Perishable : public Product {
		Date Expiry;
	public:
		Perishable();
		//std::fstream& store(std::fstream&) const;
		std::fstream& store(std::fstream&, bool newLine = true) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream&);
		const Date& expiry() const;
	};
}

#endif
