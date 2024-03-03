// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 4
// Module: Perishable
// Filename: Perishable.h
// Version 1.0
// Author	John Doe
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds {

    class Perishable :public Item {
    private:
        Date m_expiryDate{};
        char* m_handlingInstructions{};

    public:
        Perishable() = default;
        Perishable(const Perishable& src);
        ~Perishable();
        virtual Perishable* clone() const;
        Perishable& operator=(const Perishable& src);
        const Date& expiry() const;
        operator bool() const;

        int readSku(std::istream& istr);
        std::ofstream& save(std::ofstream& ofstr) const;
        std::ifstream& load(std::ifstream& ifstr);
        std::ostream& display(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);     

    };
}

#endif // SDDS_PERISHABLE_H
