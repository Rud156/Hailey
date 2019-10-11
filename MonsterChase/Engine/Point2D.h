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
		float X() const;
		float Y() const;

		// Static Operations
		friend Point2D operator+(const Point2D& point2d_1, const Point2D& point2d_2);
		friend Point2D operator-(const Point2D& point2d_1, const Point2D& point2d_2);
		friend Point2D operator*(const Point2D& point2d_1, const Point2D& point2d_2);
		friend Point2D operator*(const Point2D& point2d, const float operation);
		friend Point2D operator/(const Point2D& point2d_1, const Point2D& point2d_2);
		friend Point2D operator/(const Point2D& point2d, const float operation);

		friend bool operator==(const Point2D& point2d_1, const Point2D& point2d_2);
		friend bool operator!=(const Point2D& point2d_1, const Point2D& point2d_2);

		friend Point2D operator-(const Point2D& point2d);

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

		bool isZero() const;

		float length() const;
		float lengthSq() const;

		Point2D* copy() const;
		Point2D* normalize();

		static Point2D* Zero();
		static float distance(const Point2D& point2d_1, const Point2D& point2d_2);
		static float distanceSq(const Point2D& point2d_1, const Point2D& point2d_2);
	};
}
