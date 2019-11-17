#include "Random.h"
#include <cstdlib>

namespace Utils
{
	Random::Random() = default;

	Random::~Random() = default;

	void Random::SetSeed(unsigned int seed)
	{
		srand(seed);
	}

	int Random::RandomInRange(const int lowerIndex, const int upperIndex)
	{
		return (rand() % (upperIndex - lowerIndex + 1)) + lowerIndex;
	}
}
