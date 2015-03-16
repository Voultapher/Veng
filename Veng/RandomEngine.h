#pragma once

#include <random>
#include <SDL/SDL.h>
#include <time.h>

namespace Veng{

class RandomEngine
{
public:
	RandomEngine();
	~RandomEngine();

	float generateRandomFloat(float lowerBound, float upperBound);

private:
	//std::default_random_engine _randomGenerator();
};

}