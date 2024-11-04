
#include "LibApp.h"
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

	void LibApp::load()
	{
		cout << "Loading Data" << endl;
	}

	void LibApp::save()
	{
		cout << "Saving Data" << endl;
	}

	void LibApp::search()
	{
		cout << "Searching for publication" << endl;
	}

	void LibApp::returnPub()
	{
		search();
		cout << "Returning publication" << endl;
		cout << "Publication returned" << endl << endl;

		m_changed = true;
	}

	void LibApp::newPublication()
	{
		cout << "Adding new publication to library" << endl;
		if (confirm("Add this publication to library?") == true)
		{
			m_changed = true;
			cout << "Publication added" << endl;
		}
	}

	void LibApp::removePublication()
	{
		cout << "Removing publication from library" << endl;
		search();
		if (confirm("Remove this publication from the library?") == true)
		{
			m_changed = true;
			cout << "Publication removed" << endl << endl;
		}
	}

	void LibApp::checkOutPub()
	{
		search();
		if (confirm("Check out publication?") == true)
		{
			m_changed = true;
			cout << "Publication checked out" << endl << endl;
		}
	}

	LibApp::LibApp() : m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?")
	{
		m_mainMenu << "Add New Publication"
			<< "Remove Publication"
			<< "Checkout publication from library"
			<< "Return publication to library";

		m_exitMenu << "Save changes and exit"
			<< "Cancel and go back to the main menu";

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
					return 0; // Exit the program
				}
				else {
					cout << endl << "-------------------------------------------" << endl;
					cout << "Thanks for using Seneca Library Application" << endl;
					return 0; // Exit the program
				}
				break;
			default:
				break;
			}
		}
	}


	
	
}

	

	




