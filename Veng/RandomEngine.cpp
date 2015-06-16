#include "RandomEngine.h"

namespace Veng{

	RandomEngine::RandomEngine()
{
		init();
}


RandomEngine::~RandomEngine()
{
}

void RandomEngine::init(int seed){
	_seed = seed;
}

float RandomEngine::generateRandomFloat(float lowerBound, float upperBound){
	static std::default_random_engine randomGenerator(_seed);
	static std::uniform_real_distribution<float> randomFloat(lowerBound, upperBound);

	return randomFloat(randomGenerator);
}

}