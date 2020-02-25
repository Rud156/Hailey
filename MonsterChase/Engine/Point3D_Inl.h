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
		return _x == 0 && _y == 0;
	}

	inline Point3D Point3D::Zero()
	{
		return Point3D();
	}

	// Zero

	// Length

	inline float Point3D::length() const
	{
		return static_cast<float>(sqrt(_x * _x + _y * _y));
	}

	inline float Point3D::lengthSq() const
	{
		return _x * _x + _y * _y;
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

	// Printing

	inline std::ostream& operator<<(std::ostream& i_stream, const Point3D& i_point3d)
	{
		i_stream << "( " << i_point3d._x << ", " << i_point3d._y << ", " << i_point3d._z << " )";
		return i_stream;
	}

	// Printing
}
