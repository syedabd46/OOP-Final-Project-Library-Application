#ifndef SENECA_LIBAPP_H
#define SENECA_LIBAPP_H
#include "Menu.h"

namespace seneca {
   class LibApp {
	   bool m_changed;
	   Menu m_mainMenu;
	   Menu m_exitMenu;
   public:

	   LibApp();
	   unsigned int run();
   private:
	   bool confirm(const char* message);
	   void load();
	   void save();
	   void search();
	   void returnPub();
	   void newPublication();
	   void removePublication();
	   void checkOutPub();



   };
}
#endif // !SENECA_LIBAPP_H



