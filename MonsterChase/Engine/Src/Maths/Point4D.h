#pragma once
#include <ostream>

namespace Math
{
	class Point2D;
	class Point3D;

	class Point4D
	{
	private:
		float _x;
		float _y;
		float _z;
		float _w;

	public:
		// Constructor
		Point4D();
		Point4D(const Point2D& i_point2d, const float i_z, const float i_w);
		Point4D(const Point3D& i_point3d, const float i_w);
		Point4D(float i_x, float i_y, float i_z, float i_w);
		Point4D(const Point4D& i_Point4D);

		// Destructor
		~Point4D();

		// Getters
		[[nodiscard]] inline float X() const;
		[[nodiscard]] inline float Y() const;
		[[nodiscard]] inline float Z() const;
		[[nodiscard]] inline float W() const;

		// Static Operations
		inline friend Point4D operator+(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);
		inline friend Point4D operator-(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);
		inline friend Point4D operator*(const Point4D& i_Point4D, const float i_operation);
		inline friend Point4D operator/(const Point4D& i_Point4D, const float i_operation);

		inline friend bool operator==(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);
		inline friend bool operator!=(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);

		inline friend Point4D operator-(const Point4D& i_Point4D);

		// Modifier Operations
		Point4D operator+=(const Point4D& i_Point4D);
		Point4D operator-=(const Point4D& i_Point4D);
		Point4D operator*=(const float i_operation);
		Point4D operator/=(const float i_operation);

		inline friend std::ostream& operator<<(std::ostream& i_stream, const Point4D& i_Point4D);

		// Utility Methods
		void set(const Point4D& i_Point4D);
		void set(float i_x, float i_y, float i_z, float i_w);
		void set(int i_x, int i_y, int i_z, int i_w);
		void setX(float i_x);
		void setX(int i_x);
		void setY(float i_y);
		void setY(int i_y);
		void setZ(float i_z);
		void setZ(int i_z);
		void setW(float i_w);
		void setW(int i_w);

		[[nodiscard]] inline bool isZero() const;
		[[nodiscard]] inline float length() const;
		[[nodiscard]] inline float lengthSq() const;

		[[nodiscard]] inline Point4D copy() const;
		inline Point4D normalize();
		inline static Point4D normalize(const Point4D& i_Point4D);

		inline static Point4D Zero();
		inline static float dot(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);
		inline static float angle(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);
		inline static float distance(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);
		inline static float distanceSq(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2);
		inline static Point4D lerp(const Point4D& i_Point4D_1, const Point4D& i_Point4D_2, float i_progress);
	};
}

#include "Point4D_Inl.h"
