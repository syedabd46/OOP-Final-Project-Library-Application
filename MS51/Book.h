/*Final Project Milestone 5 part 1
Module : Book
Filename : Book.h
Version 1.0
Author	Syed Abdullah
Revision History
---------------------------------------------------------- -
Date      Reason
2024/8/9  Preliminary release
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#ifndef SENECA_BOOK_H__
#define SENECA_BOOK_H__

#include "Publication.h"

namespace seneca {
    class Book : public Publication {
    private:
        char* m_author;

        void clear();
        void copy(const Book& src);

    public:
        Book();
        Book(const Book& src);
        Book& operator=(const Book& src);
        virtual ~Book();

        virtual char type() const override;
        virtual std::ostream& write(std::ostream& os) const override;
        virtual std::istream& read(std::istream& is) override;
        virtual void set(int member_id) override;
        virtual operator bool() const override;
    };
}

#endif // SENECA_BOOK_H__
