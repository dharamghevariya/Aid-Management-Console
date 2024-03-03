// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 3
// Module: iProduct
// Filename: iProduct.cpp
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#include <iostream>
#include "iProduct.h"

namespace sdds {
	std::ostream& operator<<(std::ostream& ostr, const iProduct& iproduct) {
		iproduct.display(ostr);
		return ostr;
	}

	std::istream& operator>>(std::istream& istr, iProduct& iproduct) {
		iproduct.read(istr);
		return istr;
	}
}