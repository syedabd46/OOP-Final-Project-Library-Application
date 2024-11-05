/***********************************************************************
// OOP244 Utils Module
// File	Utils.cpp
// Version
// Date
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/

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