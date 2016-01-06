#pragma once

#include <random>
#include <SDL/SDL.h>
#include <time.h>

namespace veng{
	// I chose this solution over directly passing in a <random> distribution due to ease of use, althogh it adds a  
	// layer of abstraction and wont automatically support all possible distributions, 
	// but if the user want to write direct <random> syntax so why would he use this class
	enum class randomDistribution{ UNIFORM, BERNOULLI, BINOMIAL, NORMAL}; // add whatever distribution you need

class RandomEngine // random object for custom seed and shared usage
{
public:
	RandomEngine();
	~RandomEngine();

	void init(int seed = 2167, randomDistribution distrubution = randomDistribution::UNIFORM);

	float generateRandomFloat(float boundA, float boundB);

private:
	int _seed;
	randomDistribution _distribution;
	std::default_random_engine _randomGenerator;
};

extern float generateRandomFloatE(float lowerBound, float upperBound); // extern static function for cach friendly and fast random generation
template<typename T> extern T generateRandomE(float boundA, float boundB, randomDistribution distribution); // a bit slower but highly customizable;

}