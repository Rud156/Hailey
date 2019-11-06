#include "Point2D.h"

namespace Math
{
	Point2D::Point2D()
	{
		_x = 0;
		_y = 0;
	}

	Point2D::Point2D(const float x, const float y)
	{
		_x = x;
		_y = y;
	}

	Point2D::Point2D(const Point2D& point2d)
	{
		_x = point2d._x;
		_y = point2d._y;
	}

	Point2D::~Point2D() = default;

	Point2D Point2D::operator+=(const Point2D& point2d)
	{
		_x += point2d._x;
		_y += point2d._y;

		return *this;
	}

	Point2D Point2D::operator-=(const Point2D& point2d)
	{
		_x -= point2d._x;
		_y -= point2d._y;

		return *this;
	}

	Point2D Point2D::operator*=(const Point2D& point2d)
	{
		_x *= point2d._x;
		_y *= point2d._y;

		return *this;
	}

	Point2D Point2D::operator*=(const float operation)
	{
		_x *= operation;
		_y *= operation;

		return *this;
	}

	Point2D Point2D::operator/=(const Point2D& point2d)
	{
		_x /= point2d._x;
		_y /= point2d._y;

		return *this;
	}

	Point2D Point2D::operator/=(const float operation)
	{
		_x /= operation;
		_y /= operation;

		return *this;
	}

	void Point2D::set(const Point2D& point2d)
	{
		_x = point2d._x;
		_y = point2d._y;
	}

	void Point2D::set(const float x, const float y)
	{
		_x = x;
		_y = y;
	}

	void Point2D::setX(const float x)
	{
		_x = x;
	}

	void Point2D::setY(const float y)
	{
		_y = y;
	}
}
