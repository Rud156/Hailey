#include "stdafx.h"
#include "Point2D.h"
#include "cmath"
#include <iostream>

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

	float Point2D::X() const
	{
		return _x;
	}

	float Point2D::Y() const
	{
		return _y;
	}

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

	std::ostream& operator<<(std::ostream& stream, const Point2D& point2d)
	{
		stream << "( " << point2d._x << ", " << point2d._y << " )";
		return stream;
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

	bool Point2D::isZero() const
	{
		return _x == 0 && _y == 0;
	}

	float Point2D::length() const
	{
		return static_cast<float>(sqrt(_x * _x + _y * _y));
	}

	float Point2D::lengthSq() const
	{
		return _x * _x + _y * _y;
	}

	Point2D* Point2D::copy() const
	{
		return new Point2D(_x, _y);
	}

	Point2D* Point2D::normalize()
	{
		const float len = length();
		if (len != 0)
		{
			this->_x /= len;
			this->_y /= len;
		}

		return this;
	}

	Point2D* Point2D::Zero()
	{
		return new Point2D();
	}

	Point2D operator+(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() + point2d_2.X();
		const float y = point2d_1.Y() + point2d_2.Y();

		return Point2D(x, y);
	}

	Point2D operator-(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() - point2d_2.X();
		const float y = point2d_1.Y() - point2d_2.Y();

		return Point2D(x, y);
	}

	Point2D operator*(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() * point2d_2.X();
		const float y = point2d_1.Y() * point2d_2.Y();

		return Point2D(x, y);
	}

	Point2D operator*(const Point2D& point2d, const float operation)
	{
		const float x = point2d._x * operation;
		const float y = point2d._y * operation;

		return Point2D(x, y);
	}

	Point2D operator/(const Point2D& point2d, const float operation)
	{
		const float x = point2d._x / operation;
		const float y = point2d._y / operation;

		return Point2D(x, y);
	}

	Point2D operator-(const Point2D& point2d)
	{
		const float x = -point2d._x;
		const float y = -point2d._y;

		return Point2D(x, y);
	}

	Point2D operator/(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() / point2d_2.X();
		const float y = point2d_1.Y() / point2d_2.Y();

		return Point2D(x, y);
	}

	bool operator==(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		return point2d_1._x == point2d_2._x && point2d_1._y == point2d_2._y;
	}

	bool operator!=(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		return point2d_1._x != point2d_2._x || point2d_1._y != point2d_2._y;
	}

	float Point2D::distance(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1._x - point2d_2._x;
		const float y = point2d_1._y - point2d_2._y;

		return static_cast<float>(sqrt(x * x + y * y));
	}

	float Point2D::distanceSq(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1._x - point2d_2._x;
		const float y = point2d_1._y - point2d_2._y;

		return x * x + y * y;
	}
}
