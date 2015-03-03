#pragma once

namespace Veng{

class FpsLimiter{
public:
	FpsLimiter();
	void init(float targetFps);

	void setMaxFps(float targetFps);

	void begin();

	float end(); // end will return the current fps

private:
	void calculateFPS();

	float _maxFps;
	float _fps;
	float _frameTime;

	unsigned int _startTicks;
};


}