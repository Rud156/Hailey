#include "Random.h"

std::random_device Utils::Random::_randomDevice;
std::mt19937 Utils::Random::_generator(_randomDevice());

namespace Utils
{
	Random::Random() = default;

	void Random::SetSeed(unsigned int i_seed)
	{
		Random::_generator = std::mt19937(i_seed);
	}

	int Random::RandomInRange(const int i_lowerIndex, const int i_upperIndex)
	{
		const std::uniform_int_distribution<> dist(i_lowerIndex, i_upperIndex);
		return dist(Random::_generator);
	}

	float Random::RandomInRangeF(const float i_lowerIndex, const float i_upperIndex)
	{
		const std::uniform_real_distribution<float> dist(i_lowerIndex, i_upperIndex + 1);
		return dist(Random::_generator);
	}

	float Random::RandomValue()
	{
		const std::uniform_real_distribution<float> dist(0.0f, 1.0f);
		return dist(Random::_generator);
	}
}
