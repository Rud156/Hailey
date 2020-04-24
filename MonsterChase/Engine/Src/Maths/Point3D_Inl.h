#pragma once
#include <iostream>

namespace Math
{
	// Getters

	inline float Point3D::X() const
	{
		return _x;
	}

	inline float Point3D::Y() const
	{
		return _y;
	}

	inline float Point3D::Z() const
	{
		return _z;
	}


	// Getters

	// Zero

	inline bool Point3D::isZero() const
	{
		return _x == 0 && _y == 0 && _z == 0;
	}

	inline Point3D Point3D::Zero()
	{
		return Point3D();
	}

	// Zero

	// Length

	inline float Point3D::length() const
	{
		return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z));
	}

	inline float Point3D::lengthSq() const
	{
		return _x * _x + _y * _y + _z * _z;
	}

	// Length

	// Copy and Normalize

	inline Point3D Point3D::copy() const
	{
		return Point3D(_x, _y, _z);
	}

	inline Point3D Point3D::normalize()
	{
		const float len = length();
		if (len != 0)
		{
			this->_x /= len;
			this->_y /= len;
			this->_z /= len;
		}

		return *this;
	}

	Point3D Point3D::normalize(const Point3D& i_point3d)
	{
		const auto len = i_point3d.length();
		if (len != 0)
		{
			return i_point3d / len;
		}

		return i_point3d;
	}

	// Copy and Normalize

	// Basic Operators

	inline Point3D operator+(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const float x = i_point3d_1.X() + i_point3d_2.X();
		const float y = i_point3d_1.Y() + i_point3d_2.Y();
		const float z = i_point3d_1.Z() + i_point3d_2.Z();

		return Point3D(x, y, z);
	}

	inline Point3D operator-(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const float x = i_point3d_1.X() - i_point3d_2.X();
		const float y = i_point3d_1.Y() - i_point3d_2.Y();
		const float z = i_point3d_1.Z() - i_point3d_2.Z();

		return Point3D(x, y, z);
	}

	inline Point3D operator*(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const float x = i_point3d_1.X() * i_point3d_2.X();
		const float y = i_point3d_1.Y() * i_point3d_2.Y();
		const float z = i_point3d_1.Z() * i_point3d_2.Z();

		return Point3D(x, y, z);
	}

	inline Point3D operator*(const Point3D& i_point3d, const float i_operation)
	{
		const float x = i_point3d._x * i_operation;
		const float y = i_point3d._y * i_operation;
		const float z = i_point3d._z * i_operation;

		return Point3D(x, y, z);
	}

	inline Point3D operator/(const Point3D& i_point3d, const float i_operation)
	{
		const float x = i_point3d._x / i_operation;
		const float y = i_point3d._y / i_operation;
		const float z = i_point3d._z / i_operation;

		return Point3D(x, y, z);
	}

	inline Point3D operator-(const Point3D& i_point3d)
	{
		const float x = -i_point3d._x;
		const float y = -i_point3d._y;
		const float z = -i_point3d._z;

		return Point3D(x, y, z);
	}

	inline Point3D operator/(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const float x = i_point3d_1.X() / i_point3d_2.X();
		const float y = i_point3d_1.Y() / i_point3d_2.Y();
		const float z = i_point3d_1.Z() / i_point3d_2.Z();

		return Point3D(x, y, z);
	}

	inline bool operator==(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		return i_point3d_1._x == i_point3d_2._x &&
			i_point3d_1._y == i_point3d_2._y &&
			i_point3d_1._z == i_point3d_2._z;
	}

	inline bool operator!=(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		return i_point3d_1._x != i_point3d_2._x ||
			i_point3d_1._y != i_point3d_2._y ||
			i_point3d_1._z != i_point3d_2._z;
	}

	// Basic Operators

	// Distance

	inline float Point3D::distance(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const float x = i_point3d_1._x - i_point3d_2._x;
		const float y = i_point3d_1._y - i_point3d_2._y;
		const float z = i_point3d_1._z - i_point3d_2._z;

		return static_cast<float>(sqrt(x * x + y * y + z * z));
	}

	inline float Point3D::distanceSq(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const float x = i_point3d_1._x - i_point3d_2._x;
		const float y = i_point3d_1._y - i_point3d_2._y;
		const float z = i_point3d_1._z - i_point3d_2._z;

		return x * x + y * y + z * z;
	}

	// Distance

	// Cross, Dot, Angle

	float Point3D::dot(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const auto x = i_point3d_1._x * i_point3d_2._x;
		const auto y = i_point3d_1._y * i_point3d_2._y;
		const auto z = i_point3d_1._z * i_point3d_2._z;

		return x + y + z;
	}

	Point3D Point3D::cross(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const auto x = i_point3d_1._y * i_point3d_2._z - i_point3d_1._z * i_point3d_2._y;
		const auto y = i_point3d_1._z * i_point3d_2._x - i_point3d_1._x * i_point3d_2._z;
		const auto z = i_point3d_1._x * i_point3d_2._y + i_point3d_1._y * i_point3d_2._x;

		return Point3D(x, y, z);
	}

	float Point3D::angle(const Point3D& i_point3d_1, const Point3D& i_point3d_2)
	{
		const auto normalized_1 = normalize(i_point3d_1);
		const auto normalized_2 = normalize(i_point3d_2);

		return acos(dot(normalized_1, normalized_2));
	}

	// Cross, Dot, Angle

	// Lerp

	Point3D Point3D::lerp(const Point3D& i_point3d_1, const Point3D& i_point3d_2, float i_progress)
	{
		const float invertedProgress = 1.0f - i_progress;

		const auto x = (i_point3d_1._x * invertedProgress) + (i_point3d_2._x * i_progress);
		const auto y = (i_point3d_1._y * invertedProgress) + (i_point3d_2._y * i_progress);
		const auto z = (i_point3d_1._z * invertedProgress) + (i_point3d_2._z * i_progress);

		return Point3D(x, y, z);
	}

	// Lerp

	// Printing

	inline std::ostream& operator<<(std::ostream& i_stream, const Point3D& i_point3d)
	{
		i_stream << "( " << i_point3d._x << ", " << i_point3d._y << ", " << i_point3d._z << " )";
		return i_stream;
	}

	// Printing
}
