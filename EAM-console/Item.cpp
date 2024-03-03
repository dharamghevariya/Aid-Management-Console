// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 3
// Module: Item
// Filename: Item.cpp
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Item.h"
#include "Utils.h"

using namespace std;
namespace sdds {
    
    Item::Item(const Item& src) { // int a(b)
        *this = src;
    }

    Item& Item::operator=(const Item& src) { // a = b;
        if (this != &src) {
            m_price = src.m_price;
            m_quantityOnHand = src.m_quantityOnHand;
            m_quantityNeeded = src.m_quantityNeeded;
            m_displayLinear = src.m_displayLinear;
            m_status = src.m_status;
            m_sku = src.m_sku;

            delete[] m_description;

            if (src.m_description && src.m_description[0] != '\0') {
                m_description = new char[strlen(src.m_description) + 1];
                strcpy(m_description, src.m_description);
            }
            else {
                m_description = nullptr;
            }
        }
        return *this;
    }

    Item* Item::clone() const {
        return new Item(*this);
    }

    bool Item::linear() const {
        return m_displayLinear;
    }

    Item::~Item() {
        delete[] m_description;
        m_description = nullptr;
    }

    int Item::qtyNeeded() const {
        return m_quantityNeeded;
    }

    int Item::qty() const {
        return m_quantityOnHand;
    }

    Item::operator double() const {
        return m_price;
    }

    Item::operator bool() const {
        return m_status;
    }

    int Item::operator-=(int qty) {
        if (qty > 0) {
            m_quantityOnHand -= qty;
        }
        return m_quantityOnHand;
    }

    int Item::operator+=(int qty) {
        if (qty > 0) {
            m_quantityOnHand += qty;
        }
        return m_quantityOnHand;
    }

    void Item::linear(bool isLinear) {
        m_displayLinear = isLinear;
    }

    Item& Item::clear() {
        m_status.clear();
        return *this;
    }
    
    bool Item::operator==(int sku) const {
        return m_sku == sku;
    }

    bool Item::operator==(const char* description) const {
        if (description == nullptr || m_description == nullptr)
        {
            return false;
        }
        return(strstr(m_description, description) != nullptr);
    }


    std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (m_status) {
            if (ofstr.is_open()) {
                ofstr << m_sku << "\t"
                    << m_description << "\t"
                    << m_quantityOnHand << "\t"
                    << m_quantityNeeded << "\t"
                    << m_price;
            }
        }
        return ofstr;
    }

    std::ifstream& Item::load(std::ifstream& ifstr) {
        delete[] m_description;

        m_description = nullptr;
        ifstr >> m_sku;
        if (ifstr.fail()) {
            m_status = "Input file stream read failed!";
        }
        else {
            char temp[2000];
            ifstr.ignore();
            ifstr.getline(temp, 2000, '\t');
            m_description = new char[strlen(temp) + 1];
            strcpy(m_description, temp);

            ifstr >> m_quantityOnHand;
            ifstr.ignore();

            ifstr >> m_quantityNeeded;
            ifstr.ignore();

            ifstr >> m_price;
            ifstr.ignore(1);
        }
        return ifstr;
    }

    std::ostream& Item::display(std::ostream& ostr) const {
        if (!m_status) {
            ostr << m_status;
        }
        else {
            if (m_displayLinear) {
                ostr << std::setw(5) << m_sku 
                    << " | "
                    << std::left << std::setw(35) << std::setfill(' ') << (std::strlen(m_description) > 35 ? std::string(m_description, 35) : m_description)
                    << " | " 
                    << std::right << std::setw(4) << m_quantityOnHand 
                    << " | "
                    << std::right << std::setw(4) << m_quantityNeeded 
                    << " | "
                    << std::right << std::setw(7) << std::fixed << std::setprecision(2) << m_price 
                    << " |";
            }
            else {
                ostr << "AMA Item:" << std::endl
                    << std::setw(5) << m_sku << ": "
                    << m_description
                    << "\nQuantity Needed: " << m_quantityNeeded
                    << "\nQuantity Available: " << m_quantityOnHand
                    << "\nUnit Price: $" << std::fixed << std::setprecision(2) << m_price 
                    << "\nNeeded Purchase Fund: $" << std::fixed << std::setprecision(2) << (m_quantityNeeded * m_price) - (m_quantityOnHand * m_price) << std::endl;
            }
        }
        return ostr;
    }

    int Item::readSku(std::istream& istr) {
        m_status.clear();
        m_sku = ut.getint(40000, 99999, "SKU: ");
        return m_sku;
    }

    std::istream& Item::read(std::istream& istr) {
        delete[] m_description;
        m_description = nullptr;

        std::cout << "AMA Item:" << std::endl
            << "SKU: " << m_sku << std::endl
            << "Description: ";

        istr.ignore();
        char temp[2000];
        istr.getline(temp, 2000);
        m_description = new char[strlen(temp) + 1];
        strcpy(m_description, temp);

        m_quantityNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        m_quantityOnHand = ut.getint(0, m_quantityNeeded, "Quantity On Hand: ");
        m_price = ut.getdouble(0, 9999.00, "Unit Price: $");

        return istr;
    }

}
