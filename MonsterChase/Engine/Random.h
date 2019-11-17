#pragma once

namespace Utils
{
	class Random
	{
	private:
		Random();
		~Random();

	public:
		static void SetSeed(unsigned int seed);
		static int RandomInRange(const int lowerIndex, const int upperIndex);
	};
}
