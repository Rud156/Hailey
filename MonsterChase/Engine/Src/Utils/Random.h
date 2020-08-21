#pragma once

#include <random>

namespace Utils
{
	class Random
	{
	private:
		Random();
		~Random() = default;

		static std::random_device _randomDevice;
		static std::mt19937 _generator;

	public:
		static void SetSeed(unsigned int i_seed);
		[[nodiscard]] static int RandomInRange(const int i_lowerIndex, const int i_upperIndex);
		[[nodiscard]] static float RandomInRangeF(const float i_lowerIndex, const float i_upperIndex);
		[[nodiscard]] static float RandomValue();
	};
}
