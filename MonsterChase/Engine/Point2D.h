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
		Point2D(float i_x, float i_y);
		Point2D(const Point2D& i_point2d);

		// Destructor
		~Point2D();

		// Getters
		[[nodiscard]] inline float X() const;
		[[nodiscard]] inline float Y() const;

		// Static Operations
		inline friend Point2D operator+(const Point2D& i_point2d_1, const Point2D& i_point2d_2);
		inline friend Point2D operator-(const Point2D& i_point2d_1, const Point2D& i_point2d_2);
		inline friend Point2D operator*(const Point2D& i_point2d_1, const Point2D& i_point2d_2);
		inline friend Point2D operator*(const Point2D& i_point2d, const float i_operation);
		inline friend Point2D operator/(const Point2D& i_point2d_1, const Point2D& i_point2d_2);
		inline friend Point2D operator/(const Point2D& i_point2d, const float i_operation);

		inline friend bool operator==(const Point2D& i_point2d_1, const Point2D& i_point2d_2);
		inline friend bool operator!=(const Point2D& i_point2d_1, const Point2D& i_point2d_2);

		inline friend Point2D operator-(const Point2D& i_point2d);

		// Modifier Operations
		Point2D operator+=(const Point2D& i_point2d);
		Point2D operator-=(const Point2D& i_point2d);
		Point2D operator*=(const Point2D& i_point2d);
		Point2D operator*=(const float i_operation);
		Point2D operator/=(const Point2D& i_point2d);
		Point2D operator/=(const float i_operation);

		inline friend std::ostream& operator<<(std::ostream& i_stream, const Point2D& i_point2d);

		// Utility Methods
		void set(const Point2D& i_point2d);
		void set(float i_x, float i_y);
		void set(int i_x, int i_y);
		void setX(float i_x);
		void setX(int i_x);
		void setY(float i_y);
		void setY(int i_y);

		[[nodiscard]] inline bool isZero() const;

		[[nodiscard]] inline float length() const;
		[[nodiscard]] inline float lengthSq() const;

		[[nodiscard]] inline Point2D copy() const;
		[[nodiscard]] inline Point2D normalize();

		inline static Point2D Zero();
		inline static float distance(const Point2D& i_point2d_1, const Point2D& i_point2d_2);
		inline static float distanceSq(const Point2D& i_point2d_1, const Point2D& i_point2d_2);
	};
}

#include "Point2D_Inl.h"
