#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <iostream>
#include <sstream>

namespace seg
{
	template <class T>
	bool FromString(T& t, const std::string& s, std::ios_base& (*f)(std::ios_base&))
	{
		std::istringstream iss(s);
		return !(iss >> f >> t).fail();
	}

	template<typename T>
	std::string ToString(T t)
	{
		std::ostringstream s;
		s << t;
		return s.str();
	}
}

#endif
