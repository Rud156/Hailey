#pragma once
#include <cmath>

namespace Utils
{
	int MathUtils::Clamp(const int i_value, const int i_minValue, const int i_maxValue)
	{
		if (i_value < i_minValue)
		{
			return i_minValue;
		}
		if (i_value > i_maxValue)
		{
			return i_maxValue;
		}

		return i_value;
	}

	float MathUtils::Clamp(const float i_value, const float i_minValue, const float i_maxValue)
	{
		if (i_value < i_minValue)
		{
			return i_minValue;
		}
		if (i_value > i_maxValue)
		{
			return i_maxValue;
		}

		return i_value;
	}

	float MathUtils::Lerp(const float i_fromValue, const float i_toValue, const float i_progress)
	{
		return i_fromValue + (i_fromValue - i_toValue) * i_progress;
	}

	float MathUtils::LerpAngle(const float i_fromRadians, const float i_toRadians, const float i_progress)
	{
		const float delta = std::fmod((i_toRadians - i_fromRadians + PI2 + PI), PI2) - PI;
		return static_cast<float>(std::fmod((i_fromRadians + delta * i_progress + PI2), PI2));
	}

	float MathUtils::LerpAngleDeg(const float i_fromDegrees, const float i_toDegrees, const float i_progress)
	{
		const float delta = static_cast<float>(std::fmod((i_toDegrees - i_fromDegrees + 360 + 180), 360)) - 180;
		return static_cast<float>(std::fmod((i_fromDegrees + delta * i_progress + 360), 360));
	}

	size_t MathUtils::GetRoundNextMultiple(const size_t i_number, const unsigned i_multiple)
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

	float MathUtils::Map(const float i_inRangeStart, const float i_inRangeEnd, const float i_outRangeStart,
	                     const float i_outRangeEnd, const float i_value)
	{
		return i_outRangeStart + (i_value - i_inRangeStart) *
			(i_outRangeEnd - i_outRangeStart) / (i_inRangeEnd - i_inRangeStart);
	}

	float MathUtils::To360Deg(const float i_angle)
	{
		float angle = i_angle;

		while (angle < 0.0f)
		{
			angle += 360.0f;
		}
		while (angle >= 360.0f)
		{
			angle -= 360.0f;
		}
		

		return angle;
	}

	bool MathUtils::IsZero(const float i_value)
	{
		return std::fabs(i_value) <= FLOAT_ROUNDING_ERROR;
	}

	bool MathUtils::IsZero(const float i_value, const float i_tolerance)
	{
		return std::fabs(i_value) <= i_tolerance;
	}

	bool MathUtils::IsNan(const float i_value)
	{
		const volatile float copyValue = i_value;
		return copyValue != i_value;
	}

	bool MathUtils::IsEqual(const float i_a, const float i_b)
	{
		return std::fabs(i_a - i_b) <= FLOAT_ROUNDING_ERROR;
	}

	bool MathUtils::IsEqual(const float i_a, const float i_b, const float i_tolerance)
	{
		return std::fabs(i_a - i_b) <= i_tolerance;
	}

	bool MathUtils::AlmostEqualRelativeAndAbs(float i_a, float i_b, float i_tolerance, const float i_relTolerance)
	{
		const float diff = fabs(i_a - i_b);
		if (diff <= i_tolerance)
		{
			return true;
		}

		i_a = fabs(i_a);
		i_b = fabs(i_b);
		const float largest = (i_b > i_a) ? i_b : i_a;

		if (diff <= largest * i_relTolerance)
		{
			return true;
		}

		return false;
	}
}
