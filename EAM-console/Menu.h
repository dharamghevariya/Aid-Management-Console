// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 2
// Module: Menu
// Filename: Menu.h
// Version 1.0
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds {

	const int max_options = 15;

	class Menu {
		char* m_menuContent{};
	public:
		Menu(const char* text);
		~Menu();
		Menu(const Menu& menu) = delete;
		Menu& operator=(const Menu& menu) = delete;
		int noOfOptions(const char* text) const;
		unsigned int run() const;
	};
}

#endif // !SDDS_MENU_H




