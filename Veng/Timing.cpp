#include <SDL/SDL.h>

#include "Timing.h"


namespace Veng{

FpsLimiter::FpsLimiter(){

}

void FpsLimiter::init(float maxFps){
	setMaxFps(maxFps);
}

void FpsLimiter::setMaxFps(float maxFps){
	_maxFps = maxFps;;
}

void FpsLimiter::begin(){
	_startTicks = SDL_GetTicks(); // this will cause problems after more than 49 days of runtime
}

float FpsLimiter::end(){ // end will return the current fps
	calculateFPS();

	_frameTicks = ((SDL_GetTicks()) - _startTicks) - 1.0f; // the -1 makes that it stays below the maxFps
	if (1000.0f / _maxFps > _frameTicks){
		SDL_Delay((1000.0f / _maxFps) - _frameTicks);
	}

	return _fps;
}

void FpsLimiter::calculateFPS(){
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	int count;
	currentFrame++;

	if (currentFrame < NUM_SAMPLES){
		count = currentFrame;
	}
	else{
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++){
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0){
		_fps = 1000.0f / frameTimeAverage;
	}
	else{
		_fps = -666.0f; // the evil fps
	}

	prevTicks = currentTicks;

}


}