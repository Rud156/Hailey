#include "Utilities.h"

namespace Utils
{
	Utilities::Utilities()
	= default;

	Utilities::~Utilities()
	= default;

	size_t Utilities::GetRoundNextMultiple(const size_t i_number, const unsigned int i_multiple)
	{
		if (i_multiple == 0)
		{
			return i_number;
		}

		const size_t remainder = i_number % i_multiple;
		if (remainder == 0)
		{
			return i_number;
		}

		return i_number + i_multiple - remainder;
	}
}
