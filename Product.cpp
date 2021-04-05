/****************************
* Name: Jaron Bloom
* Email: jbloom5@myseneca.ca
* Section: C
****************************/

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Product.h"
#include "ErrorState.h"

using namespace std;
namespace AMA {
	void Product::name(const char* prod) {

		if (product != nullptr) {
			product = nullptr;
		}
		product = new char[(strlen(prod) + 1)];
		strcpy(product, prod);

	}

	const char* Product::name() const {
		return product;

	}

	const char* Product::sku() const {
		return productSku;
	}

	const char* Product::unit() const {
		return productUnit;
	}

	bool Product::taxed() const {
		return taxable;
	}

	double Product::price() const {
		return prodPrice;
	}

	double Product::cost() const {
		double total;
		if (taxed()) {
			total = prodPrice * tax;
			total += prodPrice;
			return total;
		}
		return prodPrice;
	}

	void Product::message(const char* mess) {
		Error.message(mess);
	}

	const char* Product::message() const {
		return Error.message();
	}

	bool Product::isClear() const {
		if (!(Error.isClear())) {
			return false;
		}
		else {
			return true;
		}
	}

	Product::Product(char n) {
		productType = n;
		strncpy(productSku, "Null", 5);
		strncpy(productUnit, "Null", 5);
		product = nullptr;
		quantityOnHand = 0;
		quantityNeeded = 0;
		prodPrice = 0;
		taxable = true;
		//Error = new ErrorState();
	}

	Product::Product(const char* prodSku, const char* prod, const char* unit, int qty, bool isTaxable, double price, int qtyNeed) {
		strncpy(productSku, prodSku, strlen(prodSku));
		productSku[strlen(prodSku)] = '\0';
		name(prod);
		strncpy(productUnit, unit, strlen(unit));
		productUnit[strlen(unit)] = '\0';
		quantityOnHand = qty;
		taxable = isTaxable;
		prodPrice = price;
		quantityNeeded = qtyNeed;
	}

	Product::Product(const Product& prod) {
		product = nullptr;
		*this = prod;
	}

	Product& Product::operator=(const Product& rhs) {
		if (this != &rhs) {
			if (product != nullptr)
				delete[] product;

			strcpy(productSku, rhs.productSku);
			if (rhs.product != nullptr) {
				int length = strlen(rhs.product);
				product = new char[length + 1];
				strncpy(product, rhs.product, length);
				product[length] = '\0';
			}
			else {
				product = nullptr;
			}
			productType = rhs.productType;
			strcpy(productUnit, rhs.productUnit);
			taxable = rhs.taxable;
			prodPrice = rhs.prodPrice;
			quantityOnHand = rhs.quantityOnHand;
			quantityNeeded = rhs.quantityNeeded;
		}
		return *this;
	}

	Product::~Product() {
		product = nullptr;
		delete[] product;

	}
	std::fstream& Product::store(std::fstream& file) const {
		return store(file, true);
	}

	std::fstream& Product::store(std::fstream& file, bool newLine) const {
		file << productType << "," << productSku << "," << product << "," << productUnit << "," << taxable << "," << prodPrice << "," << quantityOnHand << "," << quantityNeeded;
		if (newLine) {
			file << std::endl;
		}
		return file;
	}

	std::fstream& Product::load(std::fstream& file) {
		char tempProdSku[max_sku_length + 1];
		file.getline(tempProdSku, max_sku_length, ',');
		tempProdSku[strlen(tempProdSku)] = '\0';

		char tempProduct[max_name_length + 1];
		file.getline(tempProduct, max_name_length, ',');
		tempProduct[strlen(tempProduct)] = '\0';

		char tempProdUnit[max_unit_length + 1];
		file.getline(tempProdUnit, max_unit_length, ',');
		tempProdUnit[strlen(tempProdUnit)] = '\0';

		int tempQtyOnHand;
		int tempQtyNeeded;
		double tempProdPrice;
		int tempTax;
		bool tempTaxable;
		char comma = ',';

		file >> tempTax;
		if (tempTax == 1)
			tempTaxable = true;
		if (tempTax == 0)
			tempTaxable = false;

		file >> comma >> tempProdPrice >> comma >> tempQtyOnHand >> comma >> tempQtyNeeded;

		*this = Product(tempProdSku, tempProduct, tempProdUnit, tempQtyOnHand, tempTaxable, tempProdPrice, tempQtyNeeded);

		return file;
	}


	std::ostream& Product::write(std::ostream& os, bool linear) const {
		if (Error.isClear() == false) {
			os << Error.message();
			return os;
		}

		if (linear == false) {
			os << " Sku: " << productSku << endl;
			os << " Name (no spaces): " << product << endl;
			os << " Price: " << prodPrice << endl;
			if(taxable == true)
				os << " Price after tax: " << cost() << endl;
			if(taxable == false)
				os << " Price after tax: N/A" << endl;
			os << " Quantity on Hand: " << quantityOnHand << " " <<productUnit << endl;
			os << " Quantity needed: " << quantityNeeded;
		}
		else {
			os << setfill(' ');
			os.width(max_sku_length);
			os << left << productSku << "|";
			os.width(20);
			os << left << name() << "|";
			os.width(7);
			os << right << fixed << setprecision(2) << cost() << "|";
			os.width(4);
			os << right << quantityOnHand << "|";
			os.width(10);
			os << left << productUnit << "|";
			os.width(4);
			os << right << quantityNeeded << "|";
		}
		return os;
	}

	std::istream& Product::read(std::istream& is) {
		product = new char[max_name_length + 1];
		char option;
		cout << " Sku: ";
		is >> productSku;
		cout << " Name (no spaces): ";
		is >> product;
		cout << " Unit: ";
		is >> productUnit;
		cout << " Taxed? (y/n): ";
		is >> option;
		if (option == 'n' || option == 'N') {
			taxable = false;
		}

		if (option == 'y' || option == 'Y') {
			taxable = true;
		}

		if (option != 'n' && option != 'N' && option != 'y' && option != 'Y') {
			is.istream::setstate(std::ios::failbit);
			Error.message("Only (Y)es or (N)o are acceptable");
			return is;
		}

		if (is.fail()) {
			is.istream::setstate(std::ios::failbit);
			Error.message("Only (Y)es or (N)o are acceptable");
			return is;
		}

		cout << " Price: ";
		is >> prodPrice;
		if (is.fail()) {
			is.istream::setstate(std::ios::failbit);
			Error.message("Invalid Price Entry");
			return is;
		}

		cout << " Quantity on hand: ";
		is >> quantityOnHand;
		if (is.fail()) {
			is.istream::setstate(std::ios::failbit);
			Error.message("Invalid Quantity Entry");
			return is;
		}

		cout << " Quantity needed: ";
		is >> quantityNeeded;
		cin.ignore(1000,'\n');
		if (is.fail()) {
			is.istream::setstate(std::ios::failbit);
			Error.message("Invalid Quantity Needed Entry");
			return is;
		}
		Error.clear();
		return is;
	}

	bool Product::operator==(const char* s) const {
		int x = strcmp(productSku, s);
		if (x != 0) {
			return false;
		}
		else {
			return true;
		}
	}

	double Product::total_cost() const {
		double total;
		total = prodPrice * tax;
		double newPrice = prodPrice + total;
		return static_cast<double> (quantityOnHand * newPrice);
	}

	void Product::quantity(int prodUnits) {
		quantityOnHand = prodUnits;
	}

	bool Product::isEmpty() const {
		if (product != nullptr) {
			return false;
		}
		else {
			return true;
		}
	}

	int Product::qtyNeeded() const {
		return quantityNeeded;
	}

	int Product::quantity() const {
		return quantityOnHand;
	}

	bool Product::operator>(const iProduct& prod) const {
		if (strcmp(product, prod.name()) < 0)
			return false;

		else {
			return true;
		}
	}

	int Product::operator+=(int unit) {
		if (unit > 0) {
			quantityOnHand += unit;
		}
		return quantityOnHand;
	}

	std::ostream& operator<<(std::ostream& os, const iProduct& prod) {
		prod.write(os, true);
		return os;
	}

	std::istream& operator>>(std::istream& is, iProduct& prod) {
		prod.read(is);
		return is;
	}

	double operator+=(double& cost, const iProduct& prod) {
		cost += prod.total_cost();
			return cost;
		}
}
