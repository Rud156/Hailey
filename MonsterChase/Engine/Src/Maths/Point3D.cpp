#include "Point3D.h"
#include "Point2D.h"

namespace Math
{
	Point3D::Point3D()
	{
		_x = 0;
		_y = 0;
		_z = 0;
	}

	Point3D::Point3D(const float i_x, const float i_y, const float i_z)
	{
		_x = i_x;
		_y = i_y;
		_z = i_z;
	}

	Point3D::Point3D(const Point3D& i_point3d)
	{
		_x = i_point3d._x;
		_y = i_point3d._y;
		_z = i_point3d._z;
	}

	Point3D::Point3D(const Point2D& i_point2d, const float i_z)
	{
		_x = i_point2d.X();
		_y = i_point2d.Y();
		_z = i_z;
	}

	Point3D::~Point3D() = default;

	Point3D Point3D::operator+=(const Point3D& i_point3d)
	{
		_x += i_point3d._x;
		_y += i_point3d._y;
		_z += i_point3d._z;

		return *this;
	}

	Point3D Point3D::operator-=(const Point3D& i_point3d)
	{
		_x -= i_point3d._x;
		_y -= i_point3d._y;
		_z -= i_point3d._z;

		return *this;
	}

	Point3D Point3D::operator*=(const float i_operation)
	{
		_x *= i_operation;
		_y *= i_operation;
		_z *= i_operation;

		return *this;
	}

	Point3D Point3D::operator/=(const float i_operation)
	{
		_x /= i_operation;
		_y /= i_operation;
		_z /= i_operation;

		return *this;
	}

	void Point3D::set(const Point3D& i_point3d)
	{
		_x = i_point3d._x;
		_y = i_point3d._y;
		_z = i_point3d._z;
	}

	void Point3D::set(const float i_x, const float i_y, const float i_z)
	{
		_x = i_x;
		_y = i_y;
		_z = i_z;
	}

	void Point3D::set(const int i_x, const int i_y, const int i_z)
	{
		_x = static_cast<float>(i_x);
		_y = static_cast<float>(i_y);
		_z = static_cast<float>(i_z);
	}

	void Point3D::setX(const float i_x)
	{
		_x = i_x;
	}

	void Point3D::setX(const int i_x)
	{
		_x = static_cast<float>(i_x);
	}

	void Point3D::setY(const float i_y)
	{
		_y = i_y;
	}

	void Point3D::setY(const int i_y)
	{
		_y = static_cast<float>(i_y);
	}

	void Point3D::setZ(const float i_z)
	{
		_z = i_z;
	}

	void Point3D::setZ(const int i_z)
	{
		_z = static_cast<float>(i_z);
	}
}
