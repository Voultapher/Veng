#pragma once

#include <chrono>

namespace Veng{

class FpsLimiter{
public:
	FpsLimiter();
	void init(float targetFps, bool delay = true);

	void setMaxFps(float targetFps);

	void begin();

	float end(); // end will return the current fps
	float getFrameTime() const { return _frameTime; } // time spent working, without fps limit delay
	float getFrameTimeNano(); // in nanoseconds
	float getFrameTimeMicro(); // in nanoseconds

private:
	void calculateFPS();
	static std::chrono::high_resolution_clock _clock;
	std::chrono::time_point<std::chrono::high_resolution_clock> _start;
	std::chrono::time_point<std::chrono::high_resolution_clock> _end;

	bool _delay;
	float _maxFps;
	float _fps;
	float _frameTime; // time spent working, without fps limit delay
	float _frameTimeNano;

	unsigned int _startTicks;
};


}