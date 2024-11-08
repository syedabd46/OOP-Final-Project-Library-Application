#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <cstring>
#include <iostream>
#include <iomanip>
#include "Utils.h"

namespace seneca {

    Book::Book() : Publication(), m_author(nullptr) {}

    Book::Book(const Book& src) : Publication(src), m_author(nullptr) {
        copy(src);
    }

    Book& Book::operator=(const Book& src) {
        if (this != &src) {
            Publication::operator=(src);
            clear();
            copy(src);
        }
        return *this;
    }

    Book::~Book() {
        clear();
    }

    void Book::clear() {
        delete[] m_author;
        m_author = nullptr;
    }

    void Book::copy(const Book& src) {
        if (src.m_author) {
            m_author = new char[strlen(src.m_author) + 1];
            strcpy(m_author, src.m_author);
        }
    }

    char Book::type() const {
        return 'B';
    }

    std::ostream& Book::write(std::ostream& os) const {
        Publication::write(os);

        char authorBuffer[SENECA_AUTHOR_WIDTH + 1];
        if (m_author) {
            std::strncpy(authorBuffer, m_author, SENECA_AUTHOR_WIDTH);
            authorBuffer[SENECA_AUTHOR_WIDTH] = '\0';
        }
        else {
            authorBuffer[0] = '\0';
        }

        if (conIO(os)) {
            os << " ";
            os << std::setw(SENECA_AUTHOR_WIDTH) << std::left << std::setfill(' ') << authorBuffer << " |";
        }
        else {
            os << '\t' << authorBuffer;
        }

        return os;
    }

    std::istream& Book::read(std::istream& is) {
        char buffer[256];

        Publication::read(is);

        delete[] m_author;
        m_author = nullptr;

        if (conIO(is)) {
            is.ignore();
            std::cout << "Author: ";
        }
        else {
            is.ignore(1000, '\t');
        }

        is.get(buffer, sizeof(buffer));

        if (is) {
            size_t bufferLength = std::strlen(buffer);
            m_author = new char[bufferLength + 1];
            std::memcpy(m_author, buffer, bufferLength);
            m_author[bufferLength] = '\0';
        }

        return is;
    }
    
    void Book::set(int member_id) {
        Publication::set(member_id);
        resetDate();
    }

    Book::operator bool() const {
        return m_author != nullptr && m_author[0] != '\0' && Publication::operator bool();
    }
}
