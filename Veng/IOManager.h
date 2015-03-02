#pragma once

#include <vector>
#include <string>

namespace Veng{

	class IOManager
	{
	public:

		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};

}