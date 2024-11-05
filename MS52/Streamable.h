/*Final Project Milestone 5 part 2
Module : Streamable
Filename : Streamable.h
Version 1.0
Author	Syed Abdullah
Revision History
---------------------------------------------------------- -
Date      Reason
2024/8/9  Preliminary release
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#ifndef SENECA_STREAMABLE_H__
#define SENECA_STREAMABLE_H__

#include <iostream>

namespace seneca 
{
    class Streamable 
    {
    public:
        
        virtual std::ostream& write(std::ostream& os) const = 0;
        virtual std::istream& read(std::istream& is) = 0;
        virtual bool conIO(std::ios& io) const = 0;
        virtual operator bool() const = 0;
        virtual ~Streamable() {} 
    
    };

    std::istream& operator>>(std::istream&, Streamable&);
    std::ostream& operator<<(std::ostream&, const Streamable&);
}

#endif // SENECA_STREAMABLE_H__
