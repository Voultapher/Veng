#pragma once
#include <chrono>
#include <string>
#include <time.h>

#include "Utility.h"

namespace veng{

	

template <typename T> extern T getTimeNano(){
	static std::chrono::high_resolution_clock clock;
	static std::chrono::time_point<std::chrono::high_resolution_clock> start = clock.now();

	std::chrono::time_point<std::chrono::high_resolution_clock> end = clock.now();
	auto deltaTime = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	return static_cast<T> (deltaTime);
}

template <typename T> extern std::string getCurrentDate(){
	time_t const now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//auto test = strftime(
	return "33";// toString<time_t>(std::asctime(timeinfo));
}

}