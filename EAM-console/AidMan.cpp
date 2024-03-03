// ---------------------------------------------------------------------------
// Student Name :    Dharam Mehulbhai Ghevariya
// Student ID  :     136270220
// E-mail:           dmghevariya@myseneca.ca
// Course/Section: OOP244/NBB
// ---------------------------------------------------------------------------
// Citation and Sources...
// Final Project Milestone 2
// Module: AidMan
// Filename: AidMan.cpp
// Version 1.0
// ---------------------------------------------------------------------------
// I have done all the coding by myself and only copied the code
// that my professor provided to complete my workshops and assignments.
// ---------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "AidMan.h"
#include "Perishable.h"
#include "Utils.h"

using namespace std;
namespace sdds {
	unsigned int AidMan::menu() const {
		// Get the system date
		int year{}, month{}, day{};
		ut.getSystemDate(&year, &month, &day);

		// Display system information and date
		cout << "Aid Management System" << endl;
		cout << "Date: ";
		cout.fill('0');
		cout.width(4);
		cout << year << "/";
		cout.width(2);
		cout << month << "/";
		cout.width(2);
		cout << day << endl;

		// Display current data file
		cout << "Data file: ";
		if (m_fileName == nullptr)
			cout << "No file";
		else
			cout << m_fileName;
		cout << "\n"
			<< "---------------------------------" << endl;

		// Return the user's menu selection
		return m_mainMenu.run();
	}

	void AidMan::save() {
		// Check if a data file is specified
		if (m_fileName) {
			// Create an output file stream
			ofstream ofstr(m_fileName);

			// Check if the file is open
			if (!ofstr.is_open()) {
				cout << "Failed to open " << m_fileName << " for writing!" << endl;
			}
			else {
				int i{};
				// Loop through each iProduct and save its data
				for (i = 0; i < m_noOfiPro; i++) {
					m_iProductsPtr[i]->save(ofstr);
					ofstr << '\n';
				}
				// Close the file
				ofstr.close();
			}
		}
	}

	void AidMan::deallocate() {
		size_t i{};
		// Loop through each iProduct in reverse order
		for (i = m_noOfiPro; i > 0;) {
			--i;
			// Delete the iProduct object and set the pointer to null
			delete m_iProductsPtr[i];
			m_iProductsPtr[i] = nullptr;
		}
		// Reset the count of iProduct items to zero
		m_noOfiPro = 0;
	}

	bool AidMan::load(const char* fName) {
		bool flag{};
		// Deallocate existing resources
		delete[] m_fileName;
		m_fileName = nullptr;

		if (fName && fName[0] != '\0') {
			// Allocate memory for the file name
			m_fileName = new char[strlen(fName) + 1];
			strcpy(m_fileName, fName);
		}

		ifstream ifstr(m_fileName);

		if (!ifstr.is_open()) {
			int usrSel{};
			// Failed to open the file for reading
			cout << "Failed to open " << fName << " for reading!" << endl;
			cout << "Would you like to create a new data file?" << endl;
			usrSel = ut.getint(0, 1, "1- Yes!\n0- Exit\n> ");
			if (usrSel == 1) {
				// Create a new data file
				ofstream ofstr(m_fileName);
				if (!ofstr.is_open()) {
					cout << "Failed to create a new data file!" << endl;
					return false;
				}
				ofstr.close();
			}
			else {
				// User chose not to create a new file
				flag = false;
			}
		}
		else {
			// File opened successfully
			m_noOfiPro = 0;
			if (m_iProductsPtr) {
				// Deallocate existing iProduct items
				deallocate();
			}

			// Read records from the file
			while (m_noOfiPro <= sdds_max_num_items && !ifstr.eof()) {
				char nextChar = ifstr.peek();
				if (nextChar >= '1' && nextChar <= '9') {
					if (nextChar <= '3') {
						// Perishable item
						m_iProductsPtr[m_noOfiPro] = new Perishable;
					}
					else {
						// Non-perishable item
						m_iProductsPtr[m_noOfiPro] = new Item;
					}
					m_iProductsPtr[m_noOfiPro]->load(ifstr);

					if (*m_iProductsPtr[m_noOfiPro]) {
						// Item loaded successfully
						m_noOfiPro++;
					}
					else {
						// Item not in a good state, delete it
						delete m_iProductsPtr[m_noOfiPro];
					}
					flag = true;
				}
				else {
					// Invalid character, clear the stream and ignore the line
					ifstr.clear();
					ifstr.ignore(1000, '\n');
				}
			}
			if (m_fileName && m_noOfiPro) {
				// Display file name and the number of records loaded
				cout << "Enter file name: " << m_fileName << endl;
				cout << m_noOfiPro << " records loaded!\n" << endl;
			}
		}

		return flag;
	}

	AidMan::AidMan(const char* fileName) :
		m_mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {
		if (fileName && fileName[0] != '\0') {
			m_fileName = new char[strlen(fileName) + 1];
			strcpy(m_fileName, fileName);
		}
	}

	AidMan::~AidMan() {
		delete[] m_fileName;
		m_fileName = nullptr;
		deallocate();
	}

	void AidMan::run() {
		int usrSel{};

		do {

			usrSel = menu();

			if (usrSel != 0 && m_fileName == nullptr && usrSel != 7) {
				usrSel = 7;
			}

			switch (usrSel) {
			case 1:
				cout << "\n****List Items****\n";
				listItems();
				break;
			case 2:
				cout << "\n****Add Item****\n";
				addItems();
				break;
			case 3:
				cout << "\n****Remove Item****\n";
				removeItems();
				break;
			case 4:
				cout << "\n****Update Quantity****\n";
				updateQty();
				break;
			case 5:
				cout << "\n****Sort****\n";
				sort();
				break;
			case 6:
				cout << "\n****Ship Items****\n";
				shipItems();
				break;
			case 7:
				cout << "\n****New/Open Aid Database****\n";
				load("data.dat");
				break;
			case 0:
				cout << "Exiting Program!\n";
				save();
			}

		} while (usrSel != 0);
	}

	void AidMan::listItems() {
		int rowCount = list();
		int usrRowInput{};
		bool flag = true;

		do {
			// Prompt for row number input
			cout << "Enter row number to display details or <ENTER> to continue:" << endl;
			cout << "> ";
			cin.get();
			if (cin.peek() == '\n') {
				// User pressed enter, exit the loop
				cout << "\n";
				flag = false;
			}
			else {
				// Read user input for row number
				cin >> usrRowInput;
				if (usrRowInput >= 1 && usrRowInput <= rowCount) {
					// Display details for the selected row
					m_iProductsPtr[usrRowInput - 1]->linear(false);
					m_iProductsPtr[usrRowInput - 1]->display(cout);
					cout << "\n\n";
				}
				else {
					// Invalid input, prompt user again
					cout << "Invalid input. Please enter a valid row number." << endl;
					cin.clear();
					cin.ignore(10000, '\n');
				}
				flag = false;
			}

		} while (flag);
	}

	int AidMan::list(const char* sub_desc) const {

		int rowCount{};

		// Display header
		cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		// Loop through iProduct items
		for (int i = 0; i < m_noOfiPro; i++) {
			m_iProductsPtr[i]->linear(true);
			if (sub_desc == nullptr) {
				// Display item in linear format
				cout << "   " << i + 1 << " | ";
				m_iProductsPtr[i]->display(cout);
				cout << endl;
				rowCount++;
			}
			if (*m_iProductsPtr[i] == sub_desc) {
				// Display item conataining sub-description in description
				cout << "   " << i + 1 << " | ";
				m_iProductsPtr[i]->display(cout);
				rowCount++;
				cout << endl;
			}
			m_iProductsPtr[i]->linear(false);
		}

		// Display footer
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		return rowCount;
	}

	void AidMan::addItems() {
		// Check if the database is full
		if (m_noOfiPro >= sdds_max_num_items) {
			cout << "Database full!";
		}
		else {
			iProduct* tempiProduct{};
			int usrSel{}, usrSKU{};

			// Prompt the user to select the type of product (Perishable or Non-Perishable)
			if ((usrSel = ut.getint(0, 2, "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ")) == 0) {
				cout << "Aborted\n\n";
			}
			else {
				// Create an instance of Perishable or Item based on user selection
				if (usrSel == 1)
					tempiProduct = new Perishable;
				if (usrSel == 2)
					tempiProduct = new Item;

				// Check if the SKU already exists in the system
				if ((search(usrSKU = tempiProduct->readSku(cin))) != -1) {
					cout << "Sku: " << std::setw(5) << usrSKU << " is already in the system, try updating quantity instead.\n\n";
				}
				else {
					if (tempiProduct) {
						// Read product details from the user
						cin >> *tempiProduct;

						cout << endl;
						if (!cin.fail()) {
							// Clone and add the product to the array based on user selection
							if (usrSel == 1) {
								m_iProductsPtr[m_noOfiPro] = tempiProduct->clone();
							}
							if (usrSel == 2) {
								m_iProductsPtr[m_noOfiPro] = tempiProduct->clone();
							}
							m_noOfiPro++;
						}
						else {
							cout << *tempiProduct; // Display the error message if input fails
						}
					}
				}
				// Clean up allocated memory
				delete tempiProduct;
				tempiProduct = nullptr;
			}
		}
	}


	void AidMan::removeItems() {
		int noOfListedItems{}, usrSKU{}, searchIndx{};

		// Prompt the user for item description
		cout << "Item description: ";
		cin.clear();
		cin.ignore(10000, '\n');
		char* cStr = ut.getDynCstr(cin, '\n');

		// Display the list of items based on the provided description
		if ((noOfListedItems = list(cStr)) > 0) {
			// Prompt the user to enter SKU for the item to be removed
			usrSKU = ut.getint(10000, 99999, "Enter SKU: ");

			// Check if the SKU exists in the system
			if ((searchIndx = search(usrSKU)) != -1) {
				// Display details of the item to be removed
				cout << "Following item will be removed: \n";
				m_iProductsPtr[searchIndx]->linear(false);
				m_iProductsPtr[searchIndx]->display(cout);
				cout << endl;

				// Prompt the user for confirmation
				if (ut.getint(0, 1, "Are you sure?\n1- Yes!\n0- Exit\n> ") == 1) {
					// Remove the item from the array
					remove(searchIndx);
					cout << "Item removed!\n\n";
				}
				else {
					cout << "Aborted!\n\n";
				}
			}
			else {
				cout << "SKU not found!";
			}

			// Clean up allocated memory
			delete[] cStr;
		}
		else {
			cout << "No matches found!\n";
		}
	}


	void AidMan::updateQty() {
		int noOfListedItems{}, usrSKU{}, searchIndx{}, usrUpdate{};

		// Prompt the user for item description
		cout << "Item description: ";
		cin.clear();
		cin.ignore(10000, '\n');
		char* cStr = ut.getDynCstr(cin, '\n');

		// Display the list of items based on the provided description
		if ((noOfListedItems = list(cStr)) > 0) {
			// Prompt the user to enter SKU for the item to be updated
			usrSKU = ut.getint(10000, 99999, "Enter SKU: ");

			// Check if the SKU exists in the system
			if ((searchIndx = search(usrSKU)) != -1) {
				// Prompt the user for the type of update (Add or Reduce)
				usrUpdate = ut.getint(0, 2, "1- Add\n2- Reduce\n0- Exit\n> ");

				// Process the update based on user selection
				if (usrUpdate == 0) {
					cout << "Aborted!\n\n";
				}
				else {
					if (usrUpdate == 1) {
						// Add quantity to the item
						if (m_iProductsPtr[searchIndx]->qtyNeeded() == m_iProductsPtr[searchIndx]->qty()) {
							cout << "Quantity Needed already fulfilled!\n\n";
						}
						else {
							int qtyAdd = ut.getint(1,
								(m_iProductsPtr[searchIndx]->qtyNeeded() - m_iProductsPtr[searchIndx]->qty()),
								"Quantity to add: ");
							m_iProductsPtr[searchIndx]->operator+=(qtyAdd);
							cout << qtyAdd << " items added!\n\n";
						}
					}
					if (usrUpdate == 2) {
						// Reduce quantity from the item
						if (m_iProductsPtr[searchIndx]->qty() == 0) {
							cout << "Quantity on hand is zero!\n\n";
						}
						else {
							int qtyReduce = ut.getint(1,
								m_iProductsPtr[searchIndx]->qty(),
								"Quantity to Reduce: ");
							m_iProductsPtr[searchIndx]->operator-=(qtyReduce);
							cout << qtyReduce << " items removed!\n\n";
						}
					}
				}
			}
			else {
				cout << "SKU not found!";
			}

			// Clean up allocated memory
			delete[] cStr;
		}
		else {
			cout << "No matches found!\n";
		}
	}


	void AidMan::sort() {
		int i{}, j{};

		// Iterate through each iProduct element using Bubble Sort algorithm
		for (i = 0; i < m_noOfiPro; i++) {
			for (j = 0; j < (m_noOfiPro - i - 1); j++) {
				// Calculate the differences in quantity needed and quantity on hand for the current and next elements
				int diff1 = m_iProductsPtr[j]->qtyNeeded() - m_iProductsPtr[j]->qty();
				int diff2 = m_iProductsPtr[j + 1]->qtyNeeded() - m_iProductsPtr[j + 1]->qty();

				// Swap the elements if the difference for the current element is less than the difference for the next element
				if (diff1 < diff2) {
					// Clone and swap elements
					iProduct* temp = m_iProductsPtr[j]->clone();
					delete m_iProductsPtr[j];
					m_iProductsPtr[j] = nullptr;
					m_iProductsPtr[j] = m_iProductsPtr[j + 1]->clone();
					delete m_iProductsPtr[j + 1];
					m_iProductsPtr[j + 1] = nullptr;
					m_iProductsPtr[j + 1] = temp->clone();
					delete temp;
					temp = nullptr;
				}
			}
		}
		// Print completion message
		cout << "Sort completed!\n\n";
	}


	void AidMan::shipItems() {
		// Create an ofstream for the shipping order file
		ofstream shippingOrderFile("shippingOrder.txt");

		// Check if the file is open
		if (!shippingOrderFile.is_open()) {
			cout << "Failed to open shippingOrder.txt for writing!" << endl;
		}
		else {
			int i{}, shippedProCount{};
			Date currDate{};
			currDate.formatted(true);

			// Print shipping order header with the current date
			shippingOrderFile << "Shipping Order, Date: " << currDate << endl;

			// Print the table titles
			shippingOrderFile << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			shippingOrderFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// Iterate through each iProduct element
			for (i = 0; i < m_noOfiPro; i++) {
				// Check if quantity on hand matches quantity needed
				if (m_iProductsPtr[i]->qty() == m_iProductsPtr[i]->qtyNeeded()) {
					// Print the item details in linear format to the shipping order file
					m_iProductsPtr[i]->linear(true);
					shippingOrderFile << "   " << shippedProCount + 1 << " | ";
					m_iProductsPtr[i]->display(shippingOrderFile);
					shippingOrderFile << endl;

					// Increment the count of shipped items and remove the item from the iProduct array
					shippedProCount++;
					m_iProductsPtr[i]->linear(false);
					remove(i);
				}
			}

			// Print the table footer
			shippingOrderFile << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// Print the number of shipped items to the shipping order file
			cout << "Shipping Order for " << shippedProCount << " times saved!\n";
			cout << endl;

			// Close the shipping order file
			shippingOrderFile.close();
		}
	}


	// Function to search for an iProduct with a given SKU in the m_iProductsPtr array
	int AidMan::search(int sku) const {
		int matchedIdxValue = -1; // Initialize the index value of the matching iProduct to -1
		int i{};

		// Iterate through each iProduct in the array
		for (i = 0; i < m_noOfiPro; i++) {
			// Check if the SKU of the current iProduct matches the given SKU
			if (m_iProductsPtr[i]->operator==(sku)) {
				// If a match is found, update the matched index value
				matchedIdxValue = i;
			}
		}

		// Return the index of the matching iProduct (-1 if no match is found)
		return matchedIdxValue;
	}

	// Function to remove an iProduct at a specified index from the m_iProductsPtr array
	void AidMan::remove(int index) {
		// Check if the index is within valid bounds
		if (index < 0 || index >= m_noOfiPro) {
			cout << "Invalid index for removal." << endl;
		}
		else {
			// Delete the iProduct at the specified index and set the pointer to null
			delete m_iProductsPtr[index];
			m_iProductsPtr[index] = nullptr;

			int i{};
			// Shift elements to fill the gap left by the removed iProduct
			for (i = index; i < (m_noOfiPro - 1); i++) {
				// Clone the next iProduct and replace the current iProduct
				m_iProductsPtr[i] = m_iProductsPtr[i + 1]->clone();

				// Delete the next iProduct and set the pointer to null
				delete m_iProductsPtr[i + 1];
				m_iProductsPtr[i + 1] = nullptr;
			}

			// Set the last element in the array to null
			m_iProductsPtr[m_noOfiPro - 1] = nullptr;

			// Decrement the count of iProduct items
			m_noOfiPro--;
		}
	}

}