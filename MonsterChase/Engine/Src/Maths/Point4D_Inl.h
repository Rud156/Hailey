#pragma once

namespace Math
{
	// Getters

	inline float Point4D::X() const
	{
		return _x;
	}

	inline float Point4D::Y() const
	{
		return _y;
	}

	inline float Point4D::Z() const
	{
		return _z;
	}

	inline float Point4D::W() const
	{
		return _w;
	}


	// Getters

	// Zero

	inline bool Point4D::isZero() const
	{
		return _x == 0 && _y == 0 && _z == 0 && _w == 0;
	}

	inline Point4D Point4D::Zero()
	{
		return Point4D();
	}

	// Zero

	// Length

	inline float Point4D::length() const
	{
		return static_cast<float>(sqrt(_x * _x + _y * _y + _z * _z + _w * _w));
	}

	inline float Point4D::lengthSq() const
	{
		return _x * _x + _y * _y * _z * _z + _w * _w;
	}

	// Length

	// Copy and Normalize

	inline Point4D Point4D::copy() const
	{
		return Point4D(_x, _y, _z, _w);
	}

	inline Point4D Point4D::normalize()
	{
		const float len = length();
		if (len != 0)
		{
			this->_x /= len;
			this->_y /= len;
			this->_z /= len;
			this->_w /= len;
		}

		return *this;
	}

	Point4D Point4D::normalize(const Point4D& i_Point4D)
	{
		const auto len = i_Point4D.length();
		if (len != 0)
		{
			return i_Point4D / len;
		}

		return i_Point4D;
	}

	// Copy and Normalize

	// Basic Operators

	inline Point4D operator+(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const float x = i_Point4D_1.X() + i_Point4D_2.X();
		const float y = i_Point4D_1.Y() + i_Point4D_2.Y();
		const float z = i_Point4D_1.Z() + i_Point4D_2.Z();
		const float w = i_Point4D_1.W() + i_Point4D_2.W();

		return Point4D(x, y, z, w);
	}

	inline Point4D operator-(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const float x = i_Point4D_1.X() - i_Point4D_2.X();
		const float y = i_Point4D_1.Y() - i_Point4D_2.Y();
		const float z = i_Point4D_1.Z() - i_Point4D_2.Z();
		const float w = i_Point4D_1.W() - i_Point4D_2.W();

		return Point4D(x, y, z, w);
	}

	inline Point4D operator*(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const float x = i_Point4D_1.X() * i_Point4D_2.X();
		const float y = i_Point4D_1.Y() * i_Point4D_2.Y();
		const float z = i_Point4D_1.Z() * i_Point4D_2.Z();
		const float w = i_Point4D_1.W() * i_Point4D_2.W();

		return Point4D(x, y, z, w);
	}

	inline Point4D operator*(const Point4D& i_Point4D, const float i_operation)
	{
		const float x = i_Point4D._x * i_operation;
		const float y = i_Point4D._y * i_operation;
		const float z = i_Point4D._z * i_operation;
		const float w = i_Point4D._w * i_operation;

		return Point4D(x, y, z, w);
	}

	inline Point4D operator/(const Point4D& i_Point4D, const float i_operation)
	{
		const float x = i_Point4D._x / i_operation;
		const float y = i_Point4D._y / i_operation;
		const float z = i_Point4D._z / i_operation;
		const float w = i_Point4D._w / i_operation;

		return Point4D(x, y, z, w);
	}

	inline Point4D operator-(const Point4D& i_Point4D)
	{
		const float x = -i_Point4D._x;
		const float y = -i_Point4D._y;
		const float z = -i_Point4D._z;
		const float w = -i_Point4D._w;

		return Point4D(x, y, z, w);
	}

	inline Point4D operator/(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const float x = i_Point4D_1.X() / i_Point4D_2.X();
		const float y = i_Point4D_1.Y() / i_Point4D_2.Y();
		const float z = i_Point4D_1.Z() / i_Point4D_2.Z();
		const float w = i_Point4D_1.W() / i_Point4D_2.W();

		return Point4D(x, y, z, w);
	}

	inline bool operator==(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		return i_Point4D_1._x == i_Point4D_2._x &&
			i_Point4D_1._y == i_Point4D_2._y &&
			i_Point4D_1._z == i_Point4D_2._z &&
			i_Point4D_1._w == i_Point4D_2._w;
	}

	inline bool operator!=(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		return i_Point4D_1._x != i_Point4D_2._x ||
			i_Point4D_1._y != i_Point4D_2._y ||
			i_Point4D_1._z != i_Point4D_2._z ||
			i_Point4D_1._w != i_Point4D_2._w;
	}

	// Basic Operators

	// Distance

	inline float Point4D::distance(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const float x = i_Point4D_1._x - i_Point4D_2._x;
		const float y = i_Point4D_1._y - i_Point4D_2._y;
		const float z = i_Point4D_1._z - i_Point4D_2._z;
		const float w = i_Point4D_1._w - i_Point4D_2._w;

		return static_cast<float>(sqrt(x * x + y * y + z * z + w * w));
	}

	inline float Point4D::distanceSq(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const float x = i_Point4D_1._x - i_Point4D_2._x;
		const float y = i_Point4D_1._y - i_Point4D_2._y;
		const float z = i_Point4D_1._z - i_Point4D_2._z;
		const float w = i_Point4D_1._w - i_Point4D_2._w;

		return x * x + y * y + z * z + w * w;
	}

	// Distance

	// Cross, Dot, Angle

	float Point4D::dot(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const auto x = i_Point4D_1._x * i_Point4D_2._x;
		const auto y = i_Point4D_1._y * i_Point4D_2._y;
		const auto z = i_Point4D_1._z * i_Point4D_2._z;
		const auto w = i_Point4D_1._w * i_Point4D_2._w;

		return x + y + z + w;
	}

	float Point4D::angle(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2)
	{
		const auto normalized_1 = normalize(i_Point4D_1);
		const auto normalized_2 = normalize(i_Point4D_2);

		return acos(dot(normalized_1, normalized_2));
	}

	// Cross, Dot, Angle

	// Lerp

	Point4D Point4D::lerp(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2, float i_progress)
	{
		const float invertedProgress = 1.0f - i_progress;

		const auto x = (i_Point4D_1._x * invertedProgress) + (i_Point4D_2._x * i_progress);
		const auto y = (i_Point4D_1._y * invertedProgress) + (i_Point4D_2._y * i_progress);
		const auto z = (i_Point4D_1._z * invertedProgress) + (i_Point4D_2._z * i_progress);
		const auto w = (i_Point4D_1._w * invertedProgress) + (i_Point4D_2._w * i_progress);

		return Point4D(x, y, z, w);
	}

	// Lerp

	// Printing

	inline std::ostream& operator<<(std::ostream& i_stream, const Point4D& i_Point4D)
	{
		i_stream << "( " << i_Point4D._x << ", " << i_Point4D._y << ", " << i_Point4D._z << ", " << i_Point4D._w
			<< " )";
		return i_stream;
	}

	// Printing
}
