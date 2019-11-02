#include "Utilities.h"

namespace Utils
{
	Utilities::Utilities()
	= default;

	Utilities::~Utilities()
	= default;

	size_t Utilities::GetRoundNextMultiple(const size_t number, const unsigned int multiple)
	{
		if (multiple == 0)
		{
			return number;
		}

		const size_t remainder = number % multiple;
		if (remainder == 0)
		{
			return number;
		}

		return number + multiple - remainder;
	}
}
