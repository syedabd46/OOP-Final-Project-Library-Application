/*Final Project Milestone 5 part 6
Module : Lib
Filename : Lib.h
Version 1.0
Author	Syed Abdullah
Revision History
---------------------------------------------------------- -
Date      Reason
2024/8/9  Preliminary release
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#ifndef SENECA_LIB_H__
#define SENECA_LIB_H__
#include <iostream>

namespace seneca
{

    const int SENECA_MAX_LOAN_DAYS = 15;
    // maximum number of day a publication can be borrowed with no penalty
    const int SENECA_TITLE_WIDTH = 30;
    // The width in which the title of a publication should be printed on the console
    const int SENECA_AUTHOR_WIDTH = 15;
    // The width in which the author name of a book should be printed on the console
    const int SENECA_SHELF_ID_LEN = 4;
    // The width in which the shelf id of a publication should be printed on the console
    const int SENECA_LIBRARY_CAPACITY = 333;
    // Maximum number of publications the library can hold.

}

#endif
