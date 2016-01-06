#pragma once

#include <string>

// Global read only cach, should not be used in high performance code sections

namespace veng{

namespace Groc{
	static std::string errorLogPath("ErrorLog.txt");
}

}
