#include <fstream>

#include "IOManager.h"
#include "Errors.h"

namespace veng{

	bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer){
		std::ifstream file(filePath, std::ios::binary);
		if (file.fail()){
			perror(filePath.c_str());
			fatalError("Failed to load '" + filePath);
			return false;
		}

		file.seekg(0, std::ios::end); // seek to the end

		int fileSize = file.tellg(); // get the file size
		file.seekg(0, std::ios::beg);

		fileSize -= file.tellg(); // reduce fileSize by any header bytes

		buffer.resize(fileSize);
		file.read((char *)&(buffer[0]), fileSize); // this si safe as we only read binary
		file.close();

		return true;
	}

	bool writeToFile(std::string filePath, std::string data){
		static std::ofstream outputFile;

		outputFile.open(filePath, std::ios::app);
		if (outputFile.fail()){
			std::perror(filePath.c_str());
			return false;
		}

		outputFile  << data;
		outputFile.close();

		return true;
	}

}