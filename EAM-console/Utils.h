// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB 2237
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 1
// Module: Utils
// Filename: Utils.cpp
// Version 1.0
// Author	Fardad Soleimanloo
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds {
   const int sdds_testYear = 2023;
   const int sdds_testMon = 12;
   const int sdds_testDay = 9;
   class Utils {
      bool m_testMode = false;
   public:
      void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
      int daysOfMon(int mon, int year)const;
      void testMode(bool testmode = true);
      void alocpy(char*& destination, const char* source);
      int getint(const char* prompt = nullptr);
      int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);
      double getdouble(const char* prompt = nullptr);
      double getdouble(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr);
      char* getDynCstr(std::istream& istr = std::cin, char delim = '\n');
      char* alcpy(const char* cstr);
   };
   extern Utils ut;
}

#endif // !SDDS_UTILS_H
