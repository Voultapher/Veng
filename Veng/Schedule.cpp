#include "Schedule.h"

#include <SDL\SDL.h>

namespace veng{

Schedule::Schedule()
{
}


Schedule::~Schedule()
{
}

void Schedule::init(int timeSpan){
	_timeSpan = timeSpan;
	_startTime = SDL_GetTicks();
}

bool Schedule::ready(){
	int deltaTime = SDL_GetTicks() - _startTime;
	if (deltaTime > _timeSpan){
		_startTime = SDL_GetTicks();

		return true;
	}
	return false;
}

}