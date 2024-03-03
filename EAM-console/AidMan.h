// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 2
// Module: AidMan
// Filename: AidMan.h
// Version 1.0
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

namespace sdds {
	const int sdds_max_num_items = 100;

	class AidMan {
		char* m_fileName{};
		Menu m_mainMenu;
		iProduct* m_iProductsPtr[sdds_max_num_items]{};
		int m_noOfiPro{}; // this cannot be more than 100
		unsigned int menu() const;
		void save();
		void deallocate();
		bool load(const char* fName);
	public:
		AidMan(const char* fileName = nullptr);
		AidMan(const AidMan& aidman) = delete;
		AidMan& operator=(const AidMan& aidman) = delete;	
		~AidMan();
		void run();
		void listItems();
		void addItems();
		void removeItems();
		void updateQty();
		void sort();
		void shipItems();
		
		int list(const char* sub_desc = nullptr) const;
		int search(int sku) const;
		void remove(int index);

	};
}

#endif // !SDDS_AIDMAN_H



