// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 2
// Module: Menu
// Filename: Menu.cpp
// Version 1.0
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include "Utils.h"

using namespace std;
namespace sdds {
	Menu::Menu(const char* text) {
		int val = noOfOptions(text);
		if (val == -1 || val > (max_options - 1)) {
			m_menuContent = nullptr;
		}
		else {
			m_menuContent = new char[strlen(text) + 1];
			strcpy(m_menuContent, text);
		}
	}
	Menu::~Menu() {
		delete[] m_menuContent;
		m_menuContent = nullptr;
	}
	int Menu::noOfOptions(const char* text) const {
		int count{};
		unsigned int i{};
		char ch = 'x';
		if (text && text[0] != '\0') {
			for (i = 0; i <= strlen(text); i++) {
				if ((ch = text[i]) == '\t') {
					count++;
				}
			}
		}
		else {
			count = -1;
		}
		return (count + 1);
	}
	unsigned int Menu::run() const {

		int usrSel{};

		if (m_menuContent) {
			int menuCount(1);
			unsigned int i{};

			cout << menuCount << "- ";

			for (i = 0; i <= strlen(m_menuContent); i++) {

				if (m_menuContent[i] != '\t' && m_menuContent[i] != '\0') {
					cout << m_menuContent[i];
				}
				else {
					cout << endl;
					if(m_menuContent[i] != '\0'){
						cout << ++menuCount << "- ";
					}
				}
			}
			
			cout << "---------------------------------" << endl;
			cout << "0- Exit" << endl;
		}
		else
			cout << "Invalid Menu!" << endl;


		if (m_menuContent) {
			cout << "> ";
			usrSel = ut.getint(0, noOfOptions(m_menuContent));
		}
		else
			usrSel = 0;

		return usrSel;
	}
}
