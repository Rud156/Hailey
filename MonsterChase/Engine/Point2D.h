#pragma once
#include <ostream>

namespace Math
{
	class Point2D
	{
	private:
		float _x;
		float _y;

	public:
		// Constructor
		Point2D();
		Point2D(float x, float y);
		Point2D(const Point2D& point2d);

		// Destructor
		~Point2D();

		// Getters
		inline float X() const;
		inline float Y() const;

		// Static Operations
		inline friend Point2D operator+(const Point2D& point2d_1, const Point2D& point2d_2);
		inline friend Point2D operator-(const Point2D& point2d_1, const Point2D& point2d_2);
		inline friend Point2D operator*(const Point2D& point2d_1, const Point2D& point2d_2);
		inline friend Point2D operator*(const Point2D& point2d, const float operation);
		inline friend Point2D operator/(const Point2D& point2d_1, const Point2D& point2d_2);
		inline friend Point2D operator/(const Point2D& point2d, const float operation);

		inline friend bool operator==(const Point2D& point2d_1, const Point2D& point2d_2);
		inline friend bool operator!=(const Point2D& point2d_1, const Point2D& point2d_2);

		inline friend Point2D operator-(const Point2D& point2d);

		// Modifier Operations
		Point2D operator+=(const Point2D& point2d);
		Point2D operator-=(const Point2D& point2d);
		Point2D operator*=(const Point2D& point2d);
		Point2D operator*=(const float operation);
		Point2D operator/=(const Point2D& point2d);
		Point2D operator/=(const float operation);

		friend std::ostream& operator<<(std::ostream& stream, const Point2D& point2d);

		// Utility Methods
		void set(const Point2D& point2d);
		void set(float x, float y);
		void setX(float x);
		void setY(float y);

		inline bool isZero() const;

		inline float length() const;
		inline float lengthSq() const;

		inline Point2D copy() const;
		inline Point2D normalize();

		inline static Point2D Zero();
		inline static float distance(const Point2D& point2d_1, const Point2D& point2d_2);
		inline static float distanceSq(const Point2D& point2d_1, const Point2D& point2d_2);
	};

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
}
