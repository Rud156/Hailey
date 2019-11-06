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

		inline friend std::ostream& operator<<(std::ostream& stream, const Point2D& point2d);

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
}

#include "Point2D_Inl.h"
