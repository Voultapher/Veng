#pragma once

namespace Veng{

class FpsLimiter{
public:
	FpsLimiter();
	void init(float targetFps, bool delay = true);

	void setMaxFps(float targetFps);

	void begin();

	float end(); // end will return the current fps
	float getFrameTime() const { return _frameTime; }
	float getFramTicks() const { return _frameTicks; } // time spent working, without fps limit delay

private:
	void calculateFPS();

	bool _delay;
	float _maxFps;
	float _fps;
	float _frameTime;
	float _frameTicks; // time spent working, without fps limit delay

	unsigned int _startTicks;
};


}