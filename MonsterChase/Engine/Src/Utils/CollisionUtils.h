#pragma once

#include <SFML/Graphics.hpp>

namespace Math
{
	class Point2D;
}

namespace Utils
{
	class CollisionUtils
	{
	public:
		static bool IsPointInRect(Math::Point2D& i_center, Math::Point2D& i_extents,
		                          Math::Point2D& i_point);

		static Math::Point2D RotatePointAroundOrigin(float i_x, float i_y, float i_centerX, float i_centerY,
		                                             float i_rotationDeg);

		static Math::Point2D RotatePointAroundOrigin(Math::Point2D& i_point2d, Math::Point2D& i_center,
		                                             float i_rotationDeg);

		static Math::Point2D Get2DNormal(float i_x1, float i_y1, float i_x2, float i_y2,
		                                 bool isLeftNormal = true);

		static Math::Point2D Get2DNormal(Math::Point2D& i_point2d_1, Math::Point2D& i_point2d_2,
		                                 bool isLeftNormal = true);
	};
}
