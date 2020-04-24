#include "Point4D.h"
#include "Point3D.h"
#include "Point2D.h"

namespace Math
{
	Point4D::Point4D()
	{
		_x = 0;
		_y = 0;
		_z = 0;
		_w = 0;
	}

	Point4D::Point4D(const Point2D& i_point2d, const float i_z, const float i_w)
	{
		_x = i_point2d.X();
		_y = i_point2d.Y();
		_z = i_z;
		_w = i_w;
	}

	Point4D::Point4D(const Point3D& i_point3d, const float i_w)
	{
		_x = i_point3d.X();
		_y = i_point3d.Y();
		_z = i_point3d.Z();
		_w = i_w;
	}

	Point4D::Point4D(const float i_x, const float i_y, const float i_z, const float i_w)
	{
		_x = i_x;
		_y = i_y;
		_z = i_z;
		_w = i_w;
	}

	Point4D::Point4D(const Point4D& i_Point4D)
	{
		_x = i_Point4D._x;
		_y = i_Point4D._y;
		_z = i_Point4D._z;
		_w = i_Point4D._w;
	}

	Point4D::~Point4D() = default;

	Point4D Point4D::operator+=(const Point4D& i_Point4D)
	{
		_x += i_Point4D._x;
		_y += i_Point4D._y;
		_z += i_Point4D._z;
		_w += i_Point4D._w;

		return *this;
	}

	Point4D Point4D::operator-=(const Point4D& i_Point4D)
	{
		_x -= i_Point4D._x;
		_y -= i_Point4D._y;
		_z -= i_Point4D._z;
		_w -= i_Point4D._w;

		return *this;
	}

	Point4D Point4D::operator*=(const float i_operation)
	{
		_x *= i_operation;
		_y *= i_operation;
		_z *= i_operation;
		_w *= i_operation;

		return *this;
	}

	Point4D Point4D::operator/=(const float i_operation)
	{
		_x /= i_operation;
		_y /= i_operation;
		_z /= i_operation;
		_w /= i_operation;

		return *this;
	}

	void Point4D::set(const Point4D& i_Point4D)
	{
		_x = i_Point4D._x;
		_y = i_Point4D._y;
		_z = i_Point4D._z;
		_w = i_Point4D._w;
	}

	void Point4D::set(const float i_x, const float i_y, const float i_z, const float i_w)
	{
		_x = i_x;
		_y = i_y;
		_z = i_z;
		_w = i_w;
	}

	void Point4D::set(const int i_x, const int i_y, const int i_z, const int i_w)
	{
		_x = static_cast<float>(i_x);
		_y = static_cast<float>(i_y);
		_z = static_cast<float>(i_z);
		_w = static_cast<float>(i_w);
	}

	void Point4D::setX(const float i_x)
	{
		_x = i_x;
	}

	void Point4D::setX(const int i_x)
	{
		_x = static_cast<float>(i_x);
	}

	void Point4D::setY(const float i_y)
	{
		_y = i_y;
	}

	void Point4D::setY(const int i_y)
	{
		_y = static_cast<float>(i_y);
	}

	void Point4D::setZ(const float i_z)
	{
		_z = i_z;
	}

	void Point4D::setZ(const int i_z)
	{
		_z = static_cast<float>(i_z);
	}

	void Point4D::setW(const float i_w)
	{
		_w = i_w;
	}

	void Point4D::setW(const int i_w)
	{
		_w = static_cast<float>(i_w);
	}
}
