#pragma once

#include <string>
#include <sstream>

namespace veng{
	template<typename T> extern std::string toString(const T& t){
		std::ostringstream oss;
		oss << t;
		return oss.str();
	}

	template<typename T> extern T fromString(const std::string& s){
		std::istringstream iss(s);
		T t;
		iss >> t;
		return t;
	}

}