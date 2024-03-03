// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 1
// Module: Status
// Filename: Status.cpp
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Status.h"

namespace sdds {

	Status::Status(char* status) {
		setStatus(status);
	}

	Status::Status(const Status& src) {
		m_objState = nullptr;
		*this = src;
	}

	Status& Status::operator=(const Status& src) {
		if (this != &src) {
			m_stCode = src.m_stCode;
			delete[] m_objState;

			if (src.m_objState && src.m_objState[0] != '\0') {
				m_objState = new char[strlen(src.m_objState) + 1];
				strcpy(m_objState, src.m_objState);
			}
			else {
				m_objState = nullptr;
			}
		}
		return *this;
	}

	Status::~Status() {
		delete[] m_objState;
		m_objState = nullptr;
	}

	void Status::setStatus(char* status) {
		if (status && status[0] != '\0') {
			m_objState = new char[strlen(status) + 1];
			strcpy(m_objState, status);
			m_stCode = 0;
		}
		else {
			m_objState = nullptr;
			m_stCode = 0;
		}
	}

	Status& Status::operator=(int code) {
		m_stCode = code;
		return *this;
	}

	Status& Status::operator=(const char* cStr) {
		if (cStr && cStr[0] != '\0') {
			if (m_objState && m_objState[0] != '\0') {
				delete[] m_objState;
				m_objState = nullptr;
			}
			m_objState = new char[strlen(cStr) + 1];
			strcpy(m_objState, cStr);
		}
		return *this;
	}

	Status::operator int() const {
		return m_stCode;
	}

	Status::operator const char* () const {
		return m_objState;
	}

	Status::operator bool() const {
		return (!m_objState)
			? true : false;
	}

	Status& Status::clear() {
		delete[] m_objState;
		m_objState = nullptr;
		m_stCode = 0;
		return *this;
	}

	std::ostream& operator<<(std::ostream& ostr, const Status& st) {
		int code = st;
		const char* desc = st;

		if (!st) {
			if (code != 0) {
				ostr << "ERR#" << code << ": " << desc;
			}
			else {
				ostr << desc;
			}
		}
		return ostr;
	}
}
