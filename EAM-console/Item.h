// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 3
// Module: Item
// Filename: Item.h
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <iostream>
#include "Status.h"
#include "iProduct.h"

namespace sdds {
	class Item : public iProduct {
        double m_price{};
        int m_quantityOnHand{};
        int m_quantityNeeded{};
        char* m_description{};
        bool m_displayLinear{};

    protected:
        Status m_status{};
        int m_sku{};

        bool linear() const;

    public:
        Item() = default;
        Item(const Item& src);
        Item& operator=(const Item& src);
        virtual Item* clone() const;
        virtual ~Item();

        virtual int qtyNeeded() const;
        virtual int qty() const;
        virtual operator double() const;
        virtual operator bool() const;

        virtual int operator-=(int qty);
        virtual int operator+=(int qty);
        virtual void linear(bool isLinear);

        Item& clear();

        virtual bool operator==(int sku) const;
        virtual bool operator==(const char* description) const;

        virtual std::ofstream& save(std::ofstream& ofstr) const;
        virtual std::ifstream& load(std::ifstream& ifstr);
        virtual std::ostream& display(std::ostream& ostr) const;
        virtual int readSku(std::istream& istr) override;
        virtual std::istream& read(std::istream& istr) override;
	};
}

#endif // !SDDS_ITEM_H


