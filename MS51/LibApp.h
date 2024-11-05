/*Final Project Milestone 5 part 1
Module : LibApp
Filename : LibApp.h
Version 1.0
Author	Syed Abdullah
Revision History
---------------------------------------------------------- -
Date      Reason
2024/8/9  Preliminary release
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Menu.h"
#include "Lib.h"
#include "Book.h"
#include "Publication.h"

namespace seneca {
	class LibApp {
		char m_fileName[256];
		Publication* PPA[SENECA_LIBRARY_CAPACITY];
		int NOLP;
		int LLRN;
		bool m_changed;
		Menu m_mainMenu;
		Menu m_exitMenu;
		Menu m_pubTypeMenu; 
	public:
		LibApp(const char* fileName);
		~LibApp();
		unsigned int run();
	private:
		bool confirm(const char* message);
		void load();
		void save();
		int search(int searchMode);
		void returnPub();
		void newPublication();
		void removePublication();
		void checkOutPub();
		Publication* getPub(int libRef) const; // Method declaration
	};
}
#endif // !SENECA_LIBAPP_H

