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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::alocpy(char*& destination, const char* source) {
       delete[] destination;
       destination = nullptr;

       if (source && source[0] != '\0') {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }
   }
   int Utils::getint(const char* prompt) {
       int value{};
       bool validInput = false;

       

       while (!validInput) {
           if (!(cin >> value)) {
               cin.clear();
               cin.ignore(1000, '\n');
               cout << "Invalid Integer, retry: ";
               value = -1;
           }
           else {
               validInput = true;
           }
       }
       return value;
   }
   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
       int value{};
       bool validInput = false;

       if (prompt != nullptr) {
           cout << prompt;
       }

       while (!validInput) {

           value = getint(prompt);

           if (value < min || value > max) {
               if (errMes != nullptr) {
                   cout << errMes << ", retry: ";
               }
               else {
                   cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
               }
           }
           else {
               validInput = true;
           }
       }
       return value;
   }

   double Utils::getdouble(const char* prompt) {
       double value{};
       bool validInput = false;

       while (!validInput) {
           if (!(std::cin >> value)) {
               cin.clear();
               cin.ignore(1000, '\n');
               cout << "Invalid number, retry: ";
               value = -1.0;
           }
           else {
               validInput = true;
           }
       }
       return value;
   }

   // Implementation for getdouble within a specified range
   double Utils::getdouble(double min, double max, const char* prompt, const char* errMes) {
       
       double value{};
       bool validInput = false;

       if (prompt != nullptr) {
           cout << prompt;
       }

       while (!validInput) {
           value = getdouble(prompt);

           if (value < min || value > max) {
               if (errMes != nullptr) {
                   cout << errMes << ", retry: ";
               }
               else {
                   
                   cout << "Value out of range [" << std::fixed << std::setprecision(2) << min << "<=val<=" << max << "]: ";
               }
           }
           else {
               validInput = true;
           }
       }
       return value;
   }

   char* Utils::getDynCstr(std::istream& istr, char delim) {
       char* cstr{};
       string str;
       getline(istr, str, delim);
       if (istr) cstr = alcpy(str.c_str());
       return cstr;
   }

   char* Utils::alcpy(const char* cstr) {
       char* newStr{};
       if (cstr) {
           newStr = new char[strlen(cstr) + 1];
           strcpy(newStr, cstr);
       }
       return newStr;
   }

   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
   
}