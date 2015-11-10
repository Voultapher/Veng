#pragma once
#include <chrono>

namespace Veng{

template <typename T> extern T getTimeNano(){
	static std::chrono::high_resolution_clock clock;
	static std::chrono::time_point<std::chrono::high_resolution_clock> start = clock.now();

	std::chrono::time_point<std::chrono::high_resolution_clock> end = clock.now();
	auto deltaTime = (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
	return static_cast<T> (deltaTime);
}

}