// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 1
// Module: Date
// Filename: Date.cpp
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#include "Date.h"
#include "Utils.h"

namespace sdds {	

	bool Date::validate() {
		int curYear, curtMonth, curDay;
		ut.getSystemDate(&curYear, &curtMonth, &curDay);
		bool year = isYearValid(curYear);
		bool month = isMonthValid();
		bool day = isDayValid();
		bool valid = false;
		
		if (year && month && day) {
			m_stOfDate.clear();
			valid = true;
		}
		else {

			if (m_year == -1 || m_month == -1 || m_day == -1) {
				m_stOfDate = "Invalid date value";
				m_stOfDate = 0;
			}
			else {
				valid = false;
				if (!year) {
					m_stOfDate = "Invalid year in date";
					m_stOfDate = 1;
				}
				else {
					if (!month) {
						m_stOfDate = "Invalid month in date";
						m_stOfDate = 2;
					}
					else {
						if (!day) {
							m_stOfDate = "Invalid day in date";
							m_stOfDate = 3;
						}
					}
				}
			}
		}
		
		return valid;
	}

	bool Date::isYearValid(const int& curYear) const{

		return (m_year < curYear || m_year > maxYear)
			? false : true;
	}

	bool Date::isMonthValid() const{
		return (m_month < 1 || m_month > 12)
			? false : true;
	}

	bool Date::isDayValid() const{
		return (m_day < 1 || m_day > (ut.daysOfMon(m_month, m_year)))
			? false : true;
	}
	int Date::uniqDateInt()	const{
		return (m_year * 372 + m_month * 31 + m_day);
	}
	Date::Date() {
		ut.getSystemDate(&m_year, &m_month, &m_day);
	}
	Date::Date(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
		validate(); // !!!!! keep this in mind for the validate messege.		
	}
	bool Date::operator==(const Date& dt) const {
		return (uniqDateInt() == dt.uniqDateInt());
	}
	bool Date::operator!=(const Date& dt) const {
		return (uniqDateInt() != dt.uniqDateInt());
	}
	bool Date::operator<(const Date& dt) const {
		return (uniqDateInt() < dt.uniqDateInt());
	}
	bool Date::operator>(const Date& dt) const {
		return (uniqDateInt() > dt.uniqDateInt());
	}
	bool Date::operator<=(const Date& dt) const {
		return (uniqDateInt() <= dt.uniqDateInt());
	}
	bool Date::operator>=(const Date& dt) const {
		return (uniqDateInt() >= dt.uniqDateInt());
	}
	const Status& Date::state() const {
		return m_stOfDate;
	}
	Date& Date::formatted(bool flag) {
		m_formatted = flag;
		return *this;
	}
	Date::operator bool() const	{
		return (m_stOfDate); // !!!!! if you get error in state of the date true / false
	}

	std::ostream& Date::write(std::ostream& oStr) const	{
		if (m_formatted) {
			oStr << m_year << "/";
			oStr.fill('0');
			oStr.width(2);
			oStr << m_month << "/";
			oStr.width(2);
			oStr << m_day;
		}
		else {
			oStr << (m_year % 100);
			oStr.width(2);
			oStr << m_month;
			oStr.width(2);
			oStr << m_day;
		}
		return oStr;
	}

	std::istream& Date::read(std::istream& iStr) {
		int value{};
		int curYear, curtMonth, curDay;
		ut.getSystemDate(&curYear, &curtMonth, &curDay);
		
		if (!(iStr >> value)) {
			value = -1;
		}
		if (value < 10000) {
			m_year = curYear;
			m_month = int(value / 100);
			m_day = value % 100;
		}
		else {
			m_year = (value / 10000) + 2000;
			m_month = (value / 100) % 100;
			m_day = value % 100;
		}

		if (!validate()) {
			iStr.setstate(std::ios::badbit);			
		}

		return iStr;
	}

	std::ostream& operator<<(std::ostream& oStr, const Date& dt) {
		return dt.write(oStr);
	}

	std::istream& operator>>(std::istream& iStr, Date& dt) {
		return dt.read(iStr);
	}

	int Date::getYear() const {
		return m_year;
	}

	int Date::getMonth() const {
		return m_month;
	}

	int Date::getDay() const {
		return m_day;
	}
}