// Final Project Milestone 4
// Streamable Interface
// File    Streamable.cpp
// Version 1.0
// Author  Syed Abdullah
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// 
/////////////////////////////////////////////////////////////////

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