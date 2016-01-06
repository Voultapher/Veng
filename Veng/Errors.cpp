#include <iostream>
#include <cstdio>
#include <SDL/SDL.h>

#include "Errors.h"

#include "GROC.h"
#include "IOManager.h"
#include "Clock.h"

namespace veng{

void fatalError(std::string errorString){

	printf("\n%s\n", errorString.c_str());
	printf("\nEnter any key to exit...\n");
	char tmp = std::cin.get();
	SDL_Quit();
	exit(42);
}

void printToErrorLog(std::string errorString){
	errorString += " " + getCurrentDate<int>() + "\n";
	writeToFile(Groc::errorLogPath, errorString);
}

}