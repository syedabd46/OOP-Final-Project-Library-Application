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
