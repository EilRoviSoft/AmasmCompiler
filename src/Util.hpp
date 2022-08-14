#pragma once
//std
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace util {
	template <class Op>
	void split(const std::string& s, char delim, Op op) {
		std::stringstream ss(s);
		for (std::string item; std::getline(ss, item, delim);) {
			*op++ = item;
		}
	}
	std::vector <std::string> split(const std::string& s, char delim);
}