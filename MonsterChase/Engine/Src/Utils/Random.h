#pragma once

namespace Utils
{
	class Random
	{
	private:
		Random();
		~Random();

	public:
		static void SetSeed(unsigned int i_seed);
		[[nodiscard]] static int RandomInRange(const int i_lowerIndex, const int i_upperIndex);
	};
}
