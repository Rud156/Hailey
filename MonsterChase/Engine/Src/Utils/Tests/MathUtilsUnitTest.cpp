#include "MathUtilsUnitTest.h"
#include "../Debug.h"
#include "../MathUtils.h"

#include <cmath>

namespace Utils::Tests
{
	void MathUtilsUnitTest::RunTest()
	{
		float x = 10.00054f;
		float y = 10.00048f;

		const bool isEqual = Utils::MathUtils::IsEqual(x, y);
		Utils::Debug::LogOutputToWindow("Is Equal: %d\n", isEqual);

		x = 0.0000000005f;
		y = 0.000000000005f;

		const bool isZero = Utils::MathUtils::IsZero(y);
		Utils::Debug::LogOutputToWindow("Is Zero: %d\n", isZero);

		const bool isEqualZero = Utils::MathUtils::IsEqual(x, y);
		Utils::Debug::LogOutputToWindow("Is Equal: %d\n", isEqualZero);

		const float nanValue = NAN;
		const bool isNan = Utils::MathUtils::IsNan(nanValue);
		const bool isNotNan = !Utils::MathUtils::IsNan(x);
		Utils::Debug::LogOutputToWindow("Is Nan: %d, Is Not Nan: %d\n", isNan, isNotNan);
	}
}
