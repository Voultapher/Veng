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

	void init(int seed = 2167);

	float generateRandomFloat(float lowerBound, float upperBound);

private:
	int _seed;
};

}