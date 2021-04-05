/****************************
* Name: Jaron Bloom
* Email: jbloom5@myseneca.ca
* Section: C
****************************/

#include <iostream>
#include <cstring>
#include <fstream>
#include "ErrorState.h"
#include "iProduct.h"

#ifndef Product_h
#define Product_h
using namespace std;
namespace AMA {
	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double tax = 0.13;

	class Product : public iProduct {
		char productType;
		char productSku[max_sku_length];
		char productUnit[max_unit_length];
		char* product;
		int quantityOnHand;
		int quantityNeeded;
		double prodPrice;
		bool taxable;
		ErrorState Error;

	protected:
		void name(const char*);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char*);
		bool isClear() const;

	public:
		Product(char n = 'N');
		Product(const char*, const char*, const char*, int = 0, bool = true, double = 0, int = 0);
		Product(const Product&);
		Product& operator=(const Product&);
		~Product();
		const char* message() const;
		std::fstream& store(std::fstream&) const;
		std::fstream& store(std::fstream&, bool) const;
		std::fstream& load(std::fstream&);
		std::ostream& write(std::ostream&, bool) const;
		std::istream& read(std::istream&);
		bool operator==(const char*) const;
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const iProduct&) const;
		int operator+=(int);
	};
std::ostream& operator<<(std::ostream& os, const iProduct& prod);
std::istream& operator>>(std::istream& is, iProduct& prod);
double operator+=(double&, const Product& cost);

}
#endif // !Product_h
