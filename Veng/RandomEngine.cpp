#include "RandomEngine.h"

namespace Veng{

RandomEngine::RandomEngine()
{
}


RandomEngine::~RandomEngine()
{
}

float RandomEngine::generateRandomFloat(float lowerBound, float upperBound){
	std::default_random_engine randomGenerator(SDL_GetTicks());

	std::uniform_real_distribution<float> randomFloat(lowerBound, upperBound);
	return randomFloat(randomGenerator);
}

}