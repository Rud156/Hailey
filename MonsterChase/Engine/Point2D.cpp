#include "Point2D.h"

namespace Math
{
	Point2D::Point2D()
	{
		_x = 0;
		_y = 0;
	}

	Point2D::Point2D(const float i_x, const float i_y)
	{
		_x = i_x;
		_y = i_y;
	}

	Point2D::Point2D(const Point2D& i_point2d)
	{
		_x = i_point2d._x;
		_y = i_point2d._y;
	}

	Point2D::~Point2D() = default;

	Point2D Point2D::operator+=(const Point2D& i_point2d)
	{
		_x += i_point2d._x;
		_y += i_point2d._y;

		return *this;
	}

	Point2D Point2D::operator-=(const Point2D& i_point2d)
	{
		_x -= i_point2d._x;
		_y -= i_point2d._y;

		return *this;
	}

	Point2D Point2D::operator*=(const Point2D& i_point2d)
	{
		_x *= i_point2d._x;
		_y *= i_point2d._y;

		return *this;
	}

	Point2D Point2D::operator*=(const float i_operation)
	{
		_x *= i_operation;
		_y *= i_operation;

		return *this;
	}

	Point2D Point2D::operator/=(const Point2D& i_point2d)
	{
		_x /= i_point2d._x;
		_y /= i_point2d._y;

		return *this;
	}

	Point2D Point2D::operator/=(const float i_operation)
	{
		_x /= i_operation;
		_y /= i_operation;

		return *this;
	}

	void Point2D::set(const Point2D& i_point2d)
	{
		_x = i_point2d._x;
		_y = i_point2d._y;
	}

	void Point2D::set(const float i_x, const float i_y)
	{
		_x = i_x;
		_y = i_y;
	}

	void Point2D::set(int i_x, const int i_y)
	{
		_x = static_cast<float>(i_x);
		_y = static_cast<float>(i_y);
	}

	void Point2D::setX(const float i_x)
	{
		_x = i_x;
	}

	void Point2D::setX(int i_x)
	{
		_x = static_cast<float>(i_x);
	}

	void Point2D::setY(const float i_y)
	{
		_y = i_y;
	}

	void Point2D::setY(int i_y)
	{
		_y = static_cast<float>(i_y);
	}
}
