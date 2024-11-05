/*Final Project Milestone 5 part 1
Module : Streamable
Filename : Streamable.cpp
Version 1.0
Author	Syed Abdullah
Revision History
---------------------------------------------------------- -
Date      Reason
2024/8/9  Preliminary release
---------------------------------------------------------- -
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.*/

#include "Streamable.h"
namespace seneca
{
	std::istream& operator>>(std::istream& is, Streamable& stream)
	{
		return stream.read(is);
	}

	std::ostream& operator<<(std::ostream& os, const Streamable& stream)
	{
		if (stream) {
			return stream.write(os);
		}
		return os;
	}

}