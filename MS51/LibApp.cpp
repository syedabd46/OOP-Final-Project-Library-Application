/*Final Project Milestone 5 part 1
Module : LibApp
Filename : LibApp.cpp
Version 1.0
Author	Syed Abdullah
Revision History
---------------------------------------------------------- -
Date      Reason
2024/8/9  Preliminary release
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>
#include "LibApp.h"
#include "PublicationSelector.h"
#include <iomanip>
using namespace std;

namespace seneca {

	bool LibApp::confirm(const char* message)
	{
		Menu m1(message);
		m1 << "Yes";

		if (m1.run() == 1)
		{
			return true;
		}

		else
		{
			cout << endl;
		}

		return false;
	}

	void LibApp::load() {
		ifstream file(m_fileName); 
		
		if (!file) { 
			cerr << "Failed to open file: " << m_fileName << endl;
			return;
		}

		cout << "Loading Data" << endl;
		char type{};
		int index = 0;

		while (file >> type) {
			file.ignore(); 
			if (index >= SENECA_LIBRARY_CAPACITY) {
				cerr << "Library capacity exceeded" << endl;
				break;
			}

			Publication* pub = nullptr;
			if (type == 'P') {
				pub = new Publication();
			}
			else if (type == 'B') {
				pub = new Book();
			}

			if (pub) {
				file >> *pub; 
				PPA[index] = pub; 
				LLRN = pub->getRef(); 
				++NOLP; 
				++index; 
			}
			else {
				cerr << "Invalid publication type: " << type << endl;
				file.ignore(numeric_limits <streamsize>::max(), '\n'); 
			}
		}

		file.close();
	}

	
	void LibApp::save() {
		cout << "Saving Data" << endl;

		ofstream file(m_fileName); 
		if (!file) {
			cerr << "Failed to open file for writing: " << m_fileName << endl;
			return;
		}

		for (int i = 0; i < NOLP; ++i) {
			if (PPA[i] && PPA[i]->getRef() != 0) { 
				file << *PPA[i] << endl; 
			}
		}

		file.close(); 
		m_changed = false; 
	}

	
	int LibApp::search(int searchMode) {
		
		int type = m_pubTypeMenu.run(); 
		cin.ignore(); 

		if (type == 0) {
			cout << "Aborted!" << endl << endl;
			return 0; 
		}

		cout << "Publication Title: ";
		char searchTitle[256];
		cin.getline(searchTitle, 256);

		PublicationSelector selector("Select one of the following found matches:", 15);

		for (int i = 0; i < NOLP; ++i) {
			if (PPA[i] && PPA[i]->type() == (type == 1 ? 'B' : 'P') && *PPA[i] == searchTitle) {
				bool match = false;

				switch (searchMode) {
				case 1: 
					match = true;
					break;
				case 2: 
					if (PPA[i]->onLoan()) { 
						match = true;
					}
					break;
				case 3: 
					if (!PPA[i]->onLoan()) { 
						match = true;
					}
					break;
				default:
					cout << "Invalid search mode" << endl;
					return 0;
				}

				if (match) {
					selector << *PPA[i];
				}
			}
		}

		if (selector) {
			selector.sort(); 
			int selectedRef = selector.run();
			if (selectedRef > 0) {
				return selectedRef;
			}
		}

		cout << "Aborted!" << endl << endl;
		return 0; 
	}


	void LibApp::returnPub()
	{
		cout << "Return publication to the library" << endl;

		int selectedRef = search(2); // Use 2 for checked out items

		if (selectedRef == 0) {
			return;
		}

		Publication* pub = getPub(selectedRef);
		if (pub == nullptr) {
			cout << "Publication not found!" << endl;
			return;
		}

		cout << *pub << endl;

		if (confirm("Return Publication?")) {
			
			const int penaltyRate = 50; 
			const int gracePeriod = 15; 

			Date today; 
			Date checkoutDate = pub->checkoutDate();
			int daysLate = today - checkoutDate; 

			if (daysLate > gracePeriod) {
				
				double penalty = (daysLate - gracePeriod) * penaltyRate / 100.0;

				cout << fixed << setprecision(2);
				cout << "Please pay $" << penalty 
				<< " penalty for being " << (daysLate - gracePeriod) << " days late!" << endl;
			}
		
			pub->set(0);

			m_changed = true;
			cout << "Publication returned" << endl << endl;
		}
	}


	void LibApp::newPublication() {
		if (NOLP >= SENECA_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl << endl;
			return;
		}

		cout << "Adding new publication to the library" << endl;

		int type = m_pubTypeMenu.run(); 

		Publication* publication = nullptr;

		switch (type) {
		case 1:
			publication = new Book();
			break;
		case 2:
			publication = new Publication();
			break;
		default:
			cout << "Aborted!" << endl << endl;
			return;
		}

		if (publication) {
			cin.ignore(numeric_limits <streamsize>::max(), '\n'); 

			cin >> *publication; 

			if (cin.fail()) {
				cin.clear(); 
				cin.ignore(numeric_limits <streamsize>::max(), '\n'); 
				cout << "Aborted!" << endl;
				delete publication;
				return;
			}

			cout << "Add this publication to the library?" << endl;
			cout << " 1- Yes" << endl;
			cout << " 0- Exit" << endl;
			cout << "> ";

			int confirm = 0;
			cin >> confirm;
			cin.ignore(numeric_limits <streamsize>::max(), '\n'); 

			if (confirm != 1) {
				cout << "Aborted!" << endl;
				delete publication;
				return;
			}

			if (*publication) {
				++LLRN;
				publication->setRef(LLRN);
				PPA[NOLP++] = publication;
				m_changed = true;
				cout << "Publication added" << endl << endl;
			}
			else {
				cout << "Failed to add publication!" << endl;
				delete publication;
			}
		}
	}


	void LibApp::removePublication() {
		
		cout << "Removing publication from the library" << endl;

		int searchMode = 1; // Assuming we want to search all publications
		int selectedRef = search(searchMode); 

		if (selectedRef == 0) 
{
			return;
		}

		int indexToRemove = -1;
		for (int i = 0; i < NOLP; ++i) {
			if (PPA[i] && PPA[i]->getRef() == selectedRef) {
				indexToRemove = i;
				break;
			}
		}

		if (indexToRemove == -1) {
			cout << "Publication not found!" << endl;
			return;
		}

		cout << *PPA[indexToRemove] << endl; 
		cout << "Remove this publication from the library?\n";
		cout << " 1- Yes\n 0- Exit\n> ";

		int choice;
		cin >> choice;
		cin.ignore(); 

		if (choice == 1) {
			
			delete PPA[indexToRemove];
			PPA[indexToRemove] = nullptr;

			for (int i = indexToRemove; i < NOLP - 1; ++i) {
				PPA[i] = PPA[i + 1];
			}
			PPA[NOLP - 1] = nullptr;
			--NOLP; 

			m_changed = true; 

			cout << "Publication removed" << endl << endl;
		}
		else {
			cout << "Removal cancelled" << endl;
		}
	}
	
	
	void LibApp::checkOutPub()
	{
		cout << "Checkout publication from the library" << endl;

		int chRef = search(3); // Use 3 for available items
		if (chRef != 0) {
			
			Publication* selectedPub = getPub(chRef);

			cout << *selectedPub << endl;

			if (confirm("Check out publication?")) {
				int memberNo;
				cout << "Enter Membership number: ";
				cin >> memberNo;

				while (memberNo < 10000 || memberNo > 99999) {
					cout << "Invalid membership number, try again: ";
					cin >> memberNo;
				}

				selectedPub->set(memberNo);
				m_changed = true; 

				cout << "Publication checked out" << endl << endl;
			}
		}
		
	}


	Publication* LibApp::getPub(int libRef) const {
        for (int i = 0; i < NOLP; ++i) {
            if (PPA[i] && PPA[i]->getRef() == libRef) {
                return PPA[i];
            }
        }
        return nullptr; 
    }

	LibApp::LibApp(const char* fileName)
		: m_fileName{ "" }, 
		NOLP(0),          
		LLRN(0),          
		m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		m_pubTypeMenu("Choose the type of publication:") 
	{
		strncpy(m_fileName, fileName, sizeof(m_fileName) - 1);
		m_fileName[sizeof(m_fileName) - 1] = '\0'; 

		m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";

		m_exitMenu << "Save changes and exit"
			<< "Cancel and go back to the main menu";

		m_pubTypeMenu << "Book"
			<< "Publication";

		load();
	}

	unsigned int LibApp::run() {
		unsigned int choice;
		while (true) {
			choice = m_mainMenu.run();
			switch (choice) {
			case 1:
				newPublication();
				break;
			case 2:
				removePublication();
				break;
			case 3:
				checkOutPub();
				break;
			case 4:
				returnPub();
				break;
			case 0:
				if (m_changed) {
					unsigned int exitChoice = m_exitMenu.run();
					if (exitChoice == 1) {
						save();
					}
					else if (exitChoice == 2)
					{
						cout << endl;
						continue;
					}
					else {
						confirm("This will discard all the changes are you sure?");

					}
					cout << endl << "-------------------------------------------" << endl;
					cout << "Thanks for using Seneca Library Application" << endl;
					return 0; 
				}
				else {
					cout << endl << "-------------------------------------------" << endl;
					cout << "Thanks for using Seneca Library Application" << endl;
					return 0; 
				}
				break;
			default:
				break;
			}
		}
	}

	LibApp::~LibApp() {
		for (int i = 0; i < NOLP; ++i) {
			delete PPA[i];
		}
	}
}
