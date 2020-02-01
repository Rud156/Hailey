#pragma once
#include <ostream>

namespace Math
{
	class Point3D
	{
	private:
		float _x;
		float _y;
		float _z;

	public:
		// Constructor
		Point3D();
		Point3D(float x, float y, float z);
		Point3D(const Point3D& point3d);

		// Destructor
		~Point3D();

		// Getters
		inline float X() const;
		inline float Y() const;
		inline float Z() const;

		// Static Operations
		inline friend Point3D operator+(const Point3D& point3d_1, const Point3D& point3d_2);
		inline friend Point3D operator-(const Point3D& point3d_1, const Point3D& point3d_2);
		inline friend Point3D operator*(const Point3D& point3d_1, const Point3D& point3d_2);
		inline friend Point3D operator*(const Point3D& point3d, const float operation);
		inline friend Point3D operator/(const Point3D& point3d_1, const Point3D& point3d_2);
		inline friend Point3D operator/(const Point3D& point3d, const float operation);

		inline friend bool operator==(const Point3D& point3d_1, const Point3D& point3d_2);
		inline friend bool operator!=(const Point3D& point3d_1, const Point3D& point3d_2);

		inline friend Point3D operator-(const Point3D& point3d);

		// Modifier Operations
		Point3D operator+=(const Point3D& point3d);
		Point3D operator-=(const Point3D& point3d);
		Point3D operator*=(const Point3D& point3d);
		Point3D operator*=(const float operation);
		Point3D operator/=(const Point3D& point3d);
		Point3D operator/=(const float operation);

		inline friend std::ostream& operator<<(std::ostream& stream, const Point3D& point3d);

		// Utility Methods
		void set(const Point3D& point3d);
		void set(float x, float y, float z);
		void set(int x, int y, int z);
		void setX(float x);
		void setX(int x);
		void setY(float y);
		void setY(int y);
		void setZ(float z);
		void setZ(int z);

		inline bool isZero() const;

		inline float length() const;
		inline float lengthSq() const;

		inline Point3D copy() const;
		inline Point3D normalize();

		inline static Point3D Zero();
		inline static float distance(const Point3D& point3d_1, const Point3D& point3d_2);
		inline static float distanceSq(const Point3D& point3d_1, const Point3D& point3d_2);
	};
}

#include "Point3D_Inl.h"
