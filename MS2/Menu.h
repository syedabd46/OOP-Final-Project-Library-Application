#ifndef MENU_H
#define MENU_H

#include <iostream>

namespace seneca {

    class MenuItem {
        char* content;
        friend class Menu;

        MenuItem();  // Private constructor
        MenuItem(const char* content);  // Private constructor
        ~MenuItem();  // Destructor
        MenuItem(const MenuItem& other) = delete;  // Deleted copy constructor
        MenuItem& operator=(const MenuItem& other) = delete;  // Deleted copy assignment operator

        operator bool() const;  // Conversion to bool
        operator const char* () const;  // Conversion to const char*

        void display(std::ostream& os) const;  // Display content on ostream
    };

    class Menu {
        static const unsigned int MAX_MENU_ITEMS = 20;
        MenuItem* title;
        MenuItem* menuItems[MAX_MENU_ITEMS];
        int numItems;

    public:
        Menu();
        Menu(const char* title);
        ~Menu();
        Menu(const Menu& other) = delete;  // Deleted copy constructor
        Menu& operator=(const Menu& other) = delete;  // Deleted copy assignment operator

        void displayTitle(std::ostream& os) const;
        void display(std::ostream& os) const;
        unsigned int run() const;

        Menu& operator<<(const char* menuItemContent);
        operator bool() const;  // Conversion to bool
        operator unsigned int() const;  // Conversion to unsigned int (number of menu items)

        const char* operator[](int index) const;  // Indexing operator

        friend std::ostream& operator<<(std::ostream& os, const Menu& menu);
        unsigned int operator~() const;  // Overload operator~

    private:
        void clearMenuItems();
    };

    std::ostream& operator<<(std::ostream& os, const Menu& menu);  // Insertion operator overload

}

#endif // MENU_H
