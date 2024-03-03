// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 1
// Module: Date
// Filename: Date.h
// Version 1.0
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#pragma once
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <iostream>
#include "Status.h"

namespace sdds{

	const int maxYear = 2030;

	class Date {
		int m_year{};
		int m_month{};
		int m_day{};
		Status m_stOfDate;
		bool m_formatted = true;
		bool validate();
		bool isYearValid(const int& curYear) const;
		bool isMonthValid() const;
		bool isDayValid() const;
		int uniqDateInt() const;
	public:
		Date();
		Date(int year, int month, int day);
		bool operator==(const Date& dt) const;
		bool operator!=(const Date& dt) const;
		bool operator<(const Date& dt) const;
		
		bool operator>(const Date& dt) const;
		bool operator<=(const Date& dt) const;
		bool operator>=(const Date& dt) const;
		const Status& state() const;
		Date& formatted(bool flag);
		operator bool() const;
		std::ostream& write(std::ostream& oStr = std::cout) const;
		std::istream& read(std::istream& iStr = std::cin);
		int getYear() const;
		int getMonth() const;
		int getDay() const;
	};
	std::ostream& operator<<(std::ostream& oStr, const Date& dt);
	std::istream& operator>>(std::istream& iStr, Date& dt);
}

#endif // !SDDS_DATE_H
