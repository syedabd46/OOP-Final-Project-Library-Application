#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include <cstring>
#include <iomanip>
#include <limits>

using namespace seneca;
using namespace std;

// MenuItem Implementation

MenuItem::MenuItem() : content(nullptr) {}

MenuItem::MenuItem(const char* content) {
    if (content) {
        this->content = new char[strlen(content) + 1];
        strcpy(this->content, content);
    }
    else {
        this->content = nullptr;
    }
}

MenuItem::~MenuItem() {
    delete[] content;
}

MenuItem::operator bool() const {
    return content != nullptr;
}

MenuItem::operator const char* () const {
    return content;
}

void MenuItem::display(std::ostream& os) const {
    if (content) {
        os << content;
    }
}

// Menu Implementation

Menu::Menu() {
    title = nullptr;
    numItems = 0;
    for (unsigned int i = 0; i < MAX_MENU_ITEMS; ++i) {
        menuItems[i] = nullptr;
    }
}

Menu::Menu(const char* title) {
    numItems = 0;
    if (title) {
        this->title = new MenuItem(title);
    }
    else {
        this->title = nullptr;
    }
    for (unsigned int i = 0; i < MAX_MENU_ITEMS; ++i) {
        menuItems[i] = nullptr;
    }
}

Menu::~Menu() {
    delete title;
    clearMenuItems();
}

void Menu::displayTitle(std::ostream& os) const {
    if (title) {
        title->display(os);
    }
}

void Menu::display(std::ostream& os) const {
    displayTitle(os);
    if (numItems > 1) {
        os << ":" << endl;
    }

    if (numItems > 0) {
        for (unsigned int i = 0; i < static_cast<unsigned int>(numItems); ++i) {
            os << setw(2) << right << (i + 1) << "- ";
            menuItems[i]->display(os);
            os << endl;
        }
    }
    os << " 0- Exit" << endl << "> ";
}

unsigned int Menu::run() const {
    unsigned int choice;
    display(cout);

    while (true) {
        if (!(cin >> choice)) {
            cout << "Invalid Selection, try again: ";
            cin.clear();
            while (cin.get() != '\n');  // Clear the input buffer
        }
        else if (choice > static_cast<unsigned int>(numItems)) { // no need to check for choice < 0, as it's unsigned
            cout << "Invalid Selection, try again: ";
        }
        else {
            break;
        }
    }

    return choice;
}

Menu& Menu::operator<<(const char* menuItemContent) {
    if (numItems < static_cast<int>(MAX_MENU_ITEMS)) {
        menuItems[numItems++] = new MenuItem(menuItemContent);
    }
    return *this;
}

Menu::operator bool() const {
    return numItems > 0;
}

Menu::operator unsigned int() const {
    return static_cast<unsigned int>(numItems);
}

const char* Menu::operator[](int index) const {
    if (numItems == 0) {
        return nullptr; // Return nullptr if there are no menu items
    }
    while (index >= 0 && static_cast<unsigned int>(index) >= static_cast<unsigned int>(numItems)) {
        index -= numItems;
    }
    while (index < 0) {
        index += numItems;
    }
    return *menuItems[index];
}

void Menu::clearMenuItems() {
    for (unsigned int i = 0; i < static_cast<unsigned int>(numItems); ++i) {
        delete menuItems[i];
    }
}

ostream& seneca::operator<<(ostream& os, const Menu& menu) {
    menu.displayTitle(os);
    return os;
}

unsigned int Menu::operator~() const {
    return run();
}
