#include "CollisionUtils.h"
#include "../Maths/Point2D.h"

#include <SFML/Graphics.hpp>

#include "MathUtils.h"

namespace Utils
{
	bool CollisionUtils::IsPointInRect(Math::Point2D& i_center, Math::Point2D& i_extents,
	                                   Math::Point2D& i_point)
	{
		const Math::Point2D topLeftPosition = i_center - Math::Point2D(i_extents.X(), i_extents.Y());
		const auto sfmlPosition = sf::Vector2f(topLeftPosition.X(), topLeftPosition.Y());
		const auto sfmlSize = sf::Vector2f(i_extents.X() * 2, i_extents.Y() * 2);

		const sf::Rect<float> rect(sfmlPosition, sfmlSize);
		return rect.contains(i_point.X(), i_point.Y());
	}

	Math::Point2D CollisionUtils::RotatePointAroundOrigin(const float i_x, const float i_y,
	                                                      const float i_centerX, const float i_centerY,
	                                                      float i_rotationDeg)
	{
		i_rotationDeg = i_rotationDeg * MathUtils::Deg2Rad;

		// Translate point to origin
		const float tempX = i_x - i_centerX;
		const float tempY = i_y - i_centerY;

		// Now apply rotation
		const float rotatedX = tempX * cos(i_rotationDeg) - tempY * sin(i_rotationDeg);
		const float rotatedY = tempX * sin(i_rotationDeg) + tempY * cos(i_rotationDeg);

		// Translate back
		const float newX = rotatedX + i_centerX;
		const float newY = rotatedY + i_centerY;

		return Math::Point2D(newX, newY);
	}

	Math::Point2D CollisionUtils::RotatePointAroundOrigin(Math::Point2D& i_point2d, Math::Point2D& i_center,
	                                                      float i_rotationDeg)
	{
		return RotatePointAroundOrigin(i_point2d.X(), i_point2d.Y(), i_center.X(), i_center.Y(), i_rotationDeg);
	}

	Math::Point2D CollisionUtils::Get2DNormal(const float i_x1, const float i_y1, const float i_x2, const float i_y2,
	                                          const bool isLeftNormal)
	{
		Math::Point2D normal;

		if (isLeftNormal)
		{
			normal.setX(-(i_y2 - i_y1));
			normal.setX(i_x2 - i_x1);
		}
		else
		{
			normal.setY(i_y2 - i_y1);
			normal.setX(-(i_x2 - i_x1));
		}

		return normal;
	}

	Math::Point2D CollisionUtils::Get2DNormal(Math::Point2D& i_point2d_1, Math::Point2D& i_point2d_2,
	                                          const bool isLeftNormal)
	{
		return Get2DNormal(i_point2d_1.X(), i_point2d_1.Y(), i_point2d_2.X(), i_point2d_2.Y(), isLeftNormal);
	}
}
