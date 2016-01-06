#include "RandomEngine.h"

#include "Errors.h"

namespace veng{

	RandomEngine::RandomEngine()
{
		init();
}


RandomEngine::~RandomEngine()
{
}

void RandomEngine::init(int seed, randomDistribution distrubution){
	_seed = seed;
	_distribution = distrubution;
	_randomGenerator = std::default_random_engine(_seed);
}

float RandomEngine::generateRandomFloat(float boundA, float boundB){
	switch (_distribution){
	case randomDistribution::UNIFORM:{
		std::uniform_real_distribution<float> randomUniform(boundA, boundB);
		return randomUniform(_randomGenerator);
	}
	case randomDistribution::BERNOULLI:{
		std::bernoulli_distribution randomBernoulli(boundA);
		return randomBernoulli(_randomGenerator);
	}
	case randomDistribution::BINOMIAL:{
		std::binomial_distribution<int> randomBinomial(boundA, boundB);
		return static_cast<float> (randomBinomial(_randomGenerator));
	}
	case randomDistribution::NORMAL:{
		std::normal_distribution<float> randomNormal(boundA, boundB);
		return randomNormal(_randomGenerator);
	}
	}

	printToErrorLog("In RandomEngine.cpp function generateRandomFloat(..) _distribution set in init() has no matching randomdistribution.");
	return NULL; // this should never happen
}

float generateRandomFloatE(float lowerBound, float upperBound){
	static std::mt19937 randomGenerator(1337);
	std::uniform_real_distribution<float> randomFloat(lowerBound, upperBound);

	return randomFloat(randomGenerator);
}

template<typename T> T generateRandomE(float lowerBound, float upperBound, int seed, randomDistribution distribution){
	static std::mt19937 randomGenerator(1337);
	static std::uniform_real_distribution<float> randomFloat(lowerBound, upperBound);

	return randomFloat(randomGenerator);
}

}