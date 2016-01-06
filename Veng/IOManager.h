#pragma once

#include <vector>
#include <string>

namespace veng{

	class IOManager
	{
	public:

		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

	};

	extern bool writeToFile(std::string filePath, std::string data);
}