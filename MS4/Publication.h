// Final Project Milestone 4
// Publication Class
// File    Publication.h
// Version 1.0
// Author  Syed Abdullah
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////

#ifndef SENECA_PUBLICATION_H__
#define SENECA_PUBLICATION_H__

#include <iostream>
#include "Streamable.h"
#include "Date.h"
#include "Lib.h"

namespace seneca {
    class Publication : public Streamable {
    private:
        char* m_title;
        char m_shelfId[SENECA_SHELF_ID_LEN + 1];
        int m_membership;
        int m_libRef;
        Date m_date;

        void clear();


    public:
        Publication();
        Publication(const Publication& src);
        Publication& operator=(const Publication& src);
        virtual ~Publication();

        virtual char type() const;
        bool onLoan() const;
        Date checkoutDate() const;
        bool operator==(const char* title) const;
        operator const char* () const;
        int getRef() const;

        virtual void set(int member_id);
        void setRef(int value);
        void resetDate();

        
        virtual std::ostream& write(std::ostream& os) const override;
        virtual std::istream& read(std::istream& is) override;
        virtual bool conIO(std::ios& io) const override;
        virtual operator bool() const override;
    };
}

#endif // SENECA_PUBLICATION_H__
