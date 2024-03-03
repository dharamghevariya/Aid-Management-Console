// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 4
// Module: Perishable
// Filename: Perishable.cpp
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
#include "Perishable.h"
#include "Item.h"
#include "Status.h"
#include "Date.h"
#include "Utils.h"

namespace sdds {
    
    Perishable::Perishable(const Perishable& src){
        *this = src;
    }
    
    Perishable& Perishable::operator=(const Perishable& src) {
        if (this != &src) {

            Item::operator=(src);

            delete[] m_handlingInstructions;
            m_handlingInstructions = nullptr;
            m_expiryDate = src.m_expiryDate;

            if (src.m_handlingInstructions != nullptr) {
                m_handlingInstructions = new char[strlen(src.m_handlingInstructions) + 1];
                strcpy(m_handlingInstructions, src.m_handlingInstructions);
            }
        }
        return *this;
    }

    Perishable::~Perishable() {
        delete[] m_handlingInstructions;
        m_handlingInstructions = nullptr;
    }

    Perishable* Perishable::clone() const {
        return new Perishable(*this);
    }

    const Date& Perishable::expiry() const {
        return m_expiryDate;
    }

    Perishable::operator bool() const {
        return m_sku != 0;
    }

    int Perishable::readSku(std::istream& istr) {
        m_status.clear();
        return m_sku = ut.getint(10000, 39999, "SKU: ");
    }

    std::ofstream& Perishable::save(std::ofstream& ofstr) const {
        if (m_status) {
            Item::save(ofstr);

            ofstr << '\t' << (m_handlingInstructions ? m_handlingInstructions : "") << '\t';

            //copy of expiry date
            Date temp(m_expiryDate.getYear(), m_expiryDate.getMonth(), m_expiryDate.getDay());
            temp.formatted(false);

            ofstr << temp;
        }
        return ofstr;
    }

    std::ifstream& Perishable::load(std::ifstream& ifstr) {
        Item::load(ifstr);

        if (ifstr.fail()) {
            m_status = "Input file stream read (perishable) failed!";
        }
        else {
            delete[] m_handlingInstructions;
            m_handlingInstructions = nullptr;

            char temp[1000];
            if (ifstr.getline(temp, 1000, '\t') && isalpha(temp[0])) {
                m_handlingInstructions = new char[strlen(temp) + 1];
                strcpy(m_handlingInstructions, temp);
            }

            ifstr >> m_expiryDate;
            ifstr.ignore();
        }
        return ifstr;
    }

    std::ostream& Perishable::display(std::ostream& ostr) const {
        if (!m_status) {
            ostr << m_status;
        }
        else {
            if (Item::linear()) {
                Item::display(ostr);

                if (m_handlingInstructions && m_handlingInstructions[0] != '\0') {
                    ostr << "*";
                }
                else {
                    ostr << " ";
                }
                ostr << m_expiryDate;
            }
            else {
                ostr << "Perishable ";
                Item::display(ostr);
                ostr << "Expiry date: ";
                ostr << m_expiryDate;
                std::cout << std::endl;
                if (m_handlingInstructions && m_handlingInstructions[0] != '\0') {
                    ostr << "Handling Instructions: " << m_handlingInstructions << std::endl;
                }
            }
        }
        return ostr;
    }

    std::istream& Perishable::read(std::istream& istr) {
        Item::read(istr);
        delete[] m_handlingInstructions;
        m_handlingInstructions = nullptr;

        std::cout << "Expiry date (YYMMDD): ";
        istr >> m_expiryDate;
        istr.ignore();

        std::cout << "Handling Instructions, ENTER to skip: ";
        if (istr.peek() != '\n') {
            m_handlingInstructions = new char[1000];
            istr.getline(m_handlingInstructions, 1000);
        }
        else {
            istr.ignore();
        }

        if (istr.fail()) {
            m_status = "Perishable console date entry failed!";
        }

        return istr;
    }   
}