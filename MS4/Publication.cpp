// Final Project Milestone 4
// Publication Class
// File    Publication.cpp
// Version 1.0
// Author  Syed Abdullah
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Publication.h"
#include <string>
#include "Utils.h"

using namespace std;

namespace seneca {

    Publication::Publication() : m_date(Date()) {
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
    }

    Publication::Publication(const Publication& publication) {
        *this = publication;
    }

    Publication& Publication::operator=(const Publication& publication) {
        if (this != &publication) {
            delete[] m_title;
            m_title = nullptr;

            set(publication.m_membership);
            setRef(publication.m_libRef);
            strcpy(m_shelfId, publication.m_shelfId);
            m_date = publication.m_date;

            if (publication.m_title) {
                m_title = new char[strlen(publication.m_title) + 1];
                strcpy(m_title, publication.m_title);
            }
        }
        return *this;
    }

    Publication::~Publication() {
        delete[] m_title;
    }

    void Publication::clear() {
        delete[] m_title;
        m_title = nullptr;
        m_shelfId[0] = '\0';
        m_membership = 0;
        m_libRef = -1;
        m_date = Date();
    }

    void Publication::set(int member_id) {
        m_membership = member_id;
    }

    void Publication::setRef(int value) {
        m_libRef = value;
    }

    void Publication::resetDate() {
        m_date = Date();
    }

    char Publication::type() const {
        return 'P';
    }

    bool Publication::onLoan() const {
        return m_membership != 0;
    }

    Date Publication::checkoutDate() const {
        return m_date;
    }

    bool Publication::operator==(const char* title) const {
        return strstr(m_title, title) != nullptr;
    }

    Publication::operator const char* () const {
        return m_title;
    }

    Publication::operator bool() const {
        return m_title != nullptr && m_shelfId[0] != '\0';
    }

    int Publication::getRef() const {
        return m_libRef;
    }

    bool Publication::conIO(std::ios& io) const {
        return (&io == &std::cin) || (&io == &std::cout);
    }

    std::ostream& Publication::write(std::ostream& os) const {
        if (conIO(os)) {
            os << "| " << std::setw(SENECA_SHELF_ID_LEN) << std::setfill(' ') << m_shelfId;
            os << " | " << std::left << std::setw(SENECA_TITLE_WIDTH) << std::setfill('.');

            if (m_title && strlen(m_title) > SENECA_TITLE_WIDTH) {
                os << std::string(m_title, SENECA_TITLE_WIDTH);
            }
            else {
                os << (m_title ? m_title : "");
            }

            os << " | " << std::setw(5) << std::setfill(' ')
                << (onLoan() ? std::to_string(m_membership).c_str() : " N/A");
            os << " | " << m_date << " |";
        }
        else {
            os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t"
                << (m_title ? m_title : "") << "\t"
                << (onLoan() ? std::to_string(m_membership).c_str() : "N/A")
                << "\t" << m_date;
        }
        return os;
    }
    
    std::istream& Publication::read(std::istream& istr) {
        char titleBuffer[256];
        char shelfIdBuffer[SENECA_SHELF_ID_LEN + 1];
        int membershipNumber = 0;
        int libraryReference = 0;
        Date publicationDate;

        delete[] m_title;
        m_title = nullptr;  

        if (conIO(istr)) {
            std::cout << "Shelf No: ";
            istr.getline(shelfIdBuffer, sizeof(shelfIdBuffer));
            if (std::strlen(shelfIdBuffer) != SENECA_SHELF_ID_LEN) {
                istr.setstate(std::ios::failbit);
            }
            std::cout << "Title: ";
            istr.getline(titleBuffer, sizeof(titleBuffer));
            std::cout << "Date: ";
            istr >> publicationDate;
        }
        else {
            istr >> libraryReference;
            istr.ignore();
            istr.getline(shelfIdBuffer, sizeof(shelfIdBuffer), '\t');
            istr.getline(titleBuffer, sizeof(titleBuffer), '\t');
            istr >> membershipNumber;
            istr >> publicationDate;
        }

        if (!publicationDate) {
            istr.setstate(std::ios::failbit);
        }

        if (istr) {
            m_title = new char[std::strlen(titleBuffer) + 1];
            std::strcpy(m_title, titleBuffer);
            std::strcpy(m_shelfId, shelfIdBuffer);
            m_membership = membershipNumber;
            m_libRef = libraryReference;
            m_date = publicationDate;
        }

        return istr;
    }


}
