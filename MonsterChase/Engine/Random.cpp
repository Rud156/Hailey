#include "Random.h"
#include <cstdlib>

namespace Utils
{
	Random::Random() = default;

	Random::~Random() = default;

	void Random::SetSeed(unsigned int i_seed)
	{
		srand(i_seed);
	}

	int Random::RandomInRange(const int i_lowerIndex, const int i_upperIndex)
	{
		return (rand() % (i_upperIndex - i_lowerIndex + 1)) + i_lowerIndex;
	}
}
