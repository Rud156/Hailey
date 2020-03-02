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

	Point2D Point2D::normalize(const Point2D& i_point2d)
	{
		const float len = i_point2d.length();

		if (len != 0)
		{
			return i_point2d / len;
		}

		return i_point2d;
	}

	// Copy and Normalize

	// Basic Operators

	inline Point2D operator+(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		const float x = i_point2d_1.X() + i_point2d_2.X();
		const float y = i_point2d_1.Y() + i_point2d_2.Y();

		return Point2D(x, y);
	}

	inline Point2D operator-(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		const float x = i_point2d_1.X() - i_point2d_2.X();
		const float y = i_point2d_1.Y() - i_point2d_2.Y();

		return Point2D(x, y);
	}

	inline Point2D operator*(const Point2D& i_point2d, const float i_operation)
	{
		const float x = i_point2d._x * i_operation;
		const float y = i_point2d._y * i_operation;

		return Point2D(x, y);
	}

	inline Point2D operator*(const float operation, const Point2D& point2d)
	{
		const float x = point2d.X() * operation;
		const float y = point2d.Y() * operation;

		return Point2D(x, y);
	}

	inline Point2D operator/(const Point2D& i_point2d, const float i_operation)
	{
		const float x = i_point2d._x / i_operation;
		const float y = i_point2d._y / i_operation;

		return Point2D(x, y);
	}

	inline Point2D operator-(const Point2D& i_point2d)
	{
		const float x = -i_point2d._x;
		const float y = -i_point2d._y;

		return Point2D(x, y);
	}

	inline bool operator==(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		return i_point2d_1._x == i_point2d_2._x && i_point2d_1._y == i_point2d_2._y;
	}

	inline bool operator!=(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		return i_point2d_1._x != i_point2d_2._x || i_point2d_1._y != i_point2d_2._y;
	}

	// Basic Operators

	// Distance

	inline float Point2D::distance(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		const float x = i_point2d_1._x - i_point2d_2._x;
		const float y = i_point2d_1._y - i_point2d_2._y;

		return static_cast<float>(sqrt(x * x + y * y));
	}

	inline float Point2D::distanceSq(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		const float x = i_point2d_1._x - i_point2d_2._x;
		const float y = i_point2d_1._y - i_point2d_2._y;

		return x * x + y * y;
	}

	// Distance

	// Cross, Dot, Angle

	float Point2D::dot(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		const float x = i_point2d_1._x * i_point2d_2._x;
		const float y = i_point2d_1._y * i_point2d_2._y;

		return x + y;
	}

	float Point2D::angle(const Point2D& i_point2d_1, const Point2D& i_point2d_2)
	{
		const auto normalized_1 = normalize(i_point2d_1);
		const auto normalized_2 = normalize(i_point2d_2);

		return acos(dot(normalized_1, normalized_2));
	}

	// Cross, Dot, Angle

	// Lerp

	Point2D Point2D::lerp(const Point2D& i_point2d_1, const Point2D& i_point2d_2, float i_progress)
	{
		const float invertedProgress = 1.0f - i_progress;

		const auto x = (i_point2d_1._x * invertedProgress) + (i_point2d_2._x * i_progress);
		const auto y = (i_point2d_1._y * invertedProgress) + (i_point2d_2._y * i_progress);

		return Point2D(x, y);
	}

	// Lerp

	// Printing

	inline std::ostream& operator<<(std::ostream& i_stream, const Point2D& i_point2d)
	{
		i_stream << "( " << i_point2d._x << ", " << i_point2d._y << " )";
		return i_stream;
	}

	// Printing
}
