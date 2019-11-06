#pragma once
#include <iostream>

namespace Math
{
	// Getters

	inline float Point2D::X() const
	{
		return _x;
	}

	inline float Point2D::Y() const
	{
		return _y;
	}

	// Getters

	// Zero

	inline bool Point2D::isZero() const
	{
		return _x == 0 && _y == 0;
	}

	inline Point2D Point2D::Zero()
	{
		return Point2D();
	}

	// Zero

	// Length

	inline float Point2D::length() const
	{
		return static_cast<float>(sqrt(_x * _x + _y * _y));
	}

	inline float Point2D::lengthSq() const
	{
		return _x * _x + _y * _y;
	}

	// Length

	// Copy and Normalize

	inline Point2D Point2D::copy() const
	{
		return Point2D(_x, _y);
	}

	inline Point2D Point2D::normalize()
	{
		const float len = length();
		if (len != 0)
		{
			this->_x /= len;
			this->_y /= len;
		}

		return *this;
	}

	// Copy and Normalize

	// Basic Operators

	inline Point2D operator+(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() + point2d_2.X();
		const float y = point2d_1.Y() + point2d_2.Y();

		return Point2D(x, y);
	}

	inline Point2D operator-(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() - point2d_2.X();
		const float y = point2d_1.Y() - point2d_2.Y();

		return Point2D(x, y);
	}

	inline Point2D operator*(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() * point2d_2.X();
		const float y = point2d_1.Y() * point2d_2.Y();

		return Point2D(x, y);
	}

	inline Point2D operator*(const Point2D& point2d, const float operation)
	{
		const float x = point2d._x * operation;
		const float y = point2d._y * operation;

		return Point2D(x, y);
	}

	inline Point2D operator/(const Point2D& point2d, const float operation)
	{
		const float x = point2d._x / operation;
		const float y = point2d._y / operation;

		return Point2D(x, y);
	}

	inline Point2D operator-(const Point2D& point2d)
	{
		const float x = -point2d._x;
		const float y = -point2d._y;

		return Point2D(x, y);
	}

	inline Point2D operator/(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1.X() / point2d_2.X();
		const float y = point2d_1.Y() / point2d_2.Y();

		return Point2D(x, y);
	}

	inline bool operator==(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		return point2d_1._x == point2d_2._x && point2d_1._y == point2d_2._y;
	}

	inline bool operator!=(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		return point2d_1._x != point2d_2._x || point2d_1._y != point2d_2._y;
	}

	// Basic Operators

	// Distance

	inline float Point2D::distance(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1._x - point2d_2._x;
		const float y = point2d_1._y - point2d_2._y;

		return static_cast<float>(sqrt(x * x + y * y));
	}

	inline float Point2D::distanceSq(const Point2D& point2d_1, const Point2D& point2d_2)
	{
		const float x = point2d_1._x - point2d_2._x;
		const float y = point2d_1._y - point2d_2._y;

		return x * x + y * y;
	}

	// Distance

	// Printing

	inline std::ostream& operator<<(std::ostream& stream, const Point2D& point2d)
	{
		stream << "( " << point2d._x << ", " << point2d._y << " )";
		return stream;
	}

	// Printing
}
