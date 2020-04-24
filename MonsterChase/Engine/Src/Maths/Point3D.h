#pragma once
#include <ostream>

namespace Math
{
	class Point2D;

	class Point3D
	{
	private:
		float _x;
		float _y;
		float _z;

	public:
		// Constructor
		Point3D();
		Point3D(float i_x, float i_y, float i_z);
		Point3D(const Point3D& i_point3d);
		Point3D(const Point2D& i_point2d, float i_z);

		// Destructor
		~Point3D();

		// Getters
		[[nodiscard]] inline float X() const;
		[[nodiscard]] inline float Y() const;
		[[nodiscard]] inline float Z() const;

		// Static Operations
		inline friend Point3D operator+(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline friend Point3D operator-(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline friend Point3D operator*(const Point3D& i_point3d, const float i_operation);
		inline friend Point3D operator/(const Point3D& i_point3d, const float i_operation);

		inline friend bool operator==(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline friend bool operator!=(const Point3D& i_point3d_1, const Point3D& i_point3d_2);

		inline friend Point3D operator-(const Point3D& i_point3d);

		// Modifier Operations
		Point3D operator+=(const Point3D& i_point3d);
		Point3D operator-=(const Point3D& i_point3d);
		Point3D operator*=(const float i_operation);
		Point3D operator/=(const float i_operation);

		inline friend std::ostream& operator<<(std::ostream& i_stream, const Point3D& i_point3d);

		// Utility Methods
		void set(const Point3D& i_point3d);
		void set(float i_x, float i_y, float i_z);
		void set(int i_x, int i_y, int i_z);
		void setX(float i_x);
		void setX(int i_x);
		void setY(float i_y);
		void setY(int i_y);
		void setZ(float i_z);
		void setZ(int i_z);

		[[nodiscard]] inline bool isZero() const;
		[[nodiscard]] inline float length() const;
		[[nodiscard]] inline float lengthSq() const;

		[[nodiscard]] inline Point3D copy() const;
		inline Point3D normalize();
		inline static Point3D normalize(const Point3D& i_point3d);

		inline static Point3D Zero();
		inline static float dot(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline static Point3D cross(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline static float angle(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline static float distance(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline static float distanceSq(const Point3D& i_point3d_1, const Point3D& i_point3d_2);
		inline static Point3D lerp(const Point3D& i_point3d_1, const Point3D& i_point3d_2, float i_progress);
	};
}

#include "Point3D_Inl.h"
