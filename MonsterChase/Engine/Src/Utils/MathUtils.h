#pragma once

namespace Utils
{
	class MathUtils
	{
	private:
		inline static const float FLOAT_ROUNDING_ERROR = 0.000001f;

		MathUtils();
		~MathUtils();

	public:
		inline static const float PI = 3.1415927f;
		inline static const float PI2 = PI * 2;
		inline static const float Rad2Deg = 180.0f / PI;
		inline static const float Deg2Rad = PI / 180.0f;

		[[nodiscard]] inline static int Clamp(int i_value, int i_minValue, int i_maxValue);
		[[nodiscard]] inline static float Clamp(float i_value, float i_minValue, float i_maxValue);

		[[nodiscard]] inline static float Lerp(float i_fromValue, float i_toValue, float i_progress);
		[[nodiscard]] inline static float LerpAngle(float i_fromRadians, float i_toRadians, float i_progress);
		[[nodiscard]] inline static float LerpAngleDeg(float i_fromDegrees, float i_toDegrees, float i_progress);

		[[nodiscard]] inline static size_t GetRoundNextMultiple(size_t i_number, unsigned int i_multiple);
		[[nodiscard]] inline static float Map(float i_inRangeStart, float i_inRangeEnd, float i_outRangeStart, float i_outRangeEnd, float i_value);

		[[nodiscard]] inline static bool IsZero(float i_value);
		[[nodiscard]] inline static bool IsZero(float i_value, float i_tolerance);
		[[nodiscard]] inline static bool IsNan(float i_value);

		[[nodiscard]] inline static bool IsEqual(float i_a, float i_b);
		[[nodiscard]] inline static bool IsEqual(float i_a, float i_b, float i_tolerance);
		[[nodiscard]] inline static bool AlmostEqualRelativeAndAbs(float i_a, float i_b, float i_tolerance, float i_relTolerance);
	};
}

#include "MathUtils_Inl.h"
