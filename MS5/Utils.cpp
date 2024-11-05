/*Final Project Milestone 5 part 6
Module : Utils
Filename : Utils.cpp
Version 1.0
Author	Syed Abdullah
Revision History
---------------------------------------------------------- -
Date      Reason
2024/8/9  Preliminary release
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#include "Utils.h"
namespace seneca 
{

    void Strncpy(char* destination, const char* source, int length) {
        int index = 0;
        bool sourceShorter = false;

        if (destination != nullptr && source != nullptr && length > 0) {
            while (index < length && !sourceShorter) {
                if (source[index] == '\0') {
                    sourceShorter = true;
                }
                else {
                    destination[index] = source[index];
                    index++;
                }
            }

            if (sourceShorter) {
                destination[index] = '\0';
            }
            else {
                destination[length] = '\0';
            }
        }
    }

}