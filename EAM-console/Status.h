// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 1
// Module: Status
// Filename: Status.h
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#pragma once
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>

namespace sdds {
	class Status {
		char* m_objState = nullptr;
		int m_stCode{};
		void setStatus(char* status);
	public:
		Status(char* status = nullptr);
		Status(const Status& src);
		Status& operator=(const Status& src);
		~Status();
		Status& operator=(int code);
		Status& operator=(const char* cStr);
		operator int() const;
		operator const char* () const;
		operator bool() const;
		Status& clear();
	};

	std::ostream& operator<<(std::ostream& ostr, const Status& st);
}

#endif // !SDDS_STATUS_H