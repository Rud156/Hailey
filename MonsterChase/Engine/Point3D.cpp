#include "Point3D.h"

namespace Math
{
	Point3D::Point3D()
	{
		_x = 0;
		_y = 0;
		_z = 0;
	}

	Point3D::Point3D(const float x, const float y, const float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	Point3D::Point3D(const Point3D& point3d)
	{
		_x = point3d._x;
		_y = point3d._y;
		_z = point3d._z;
	}

	Point3D::~Point3D() = default;

	Point3D Point3D::operator+=(const Point3D& point3d)
	{
		_x += point3d._x;
		_y += point3d._y;
		_z += point3d._z;

		return *this;
	}

	Point3D Point3D::operator-=(const Point3D& point3d)
	{
		_x -= point3d._x;
		_y -= point3d._y;
		_z -= point3d._z;

		return *this;
	}

	Point3D Point3D::operator*=(const Point3D& point3d)
	{
		_x *= point3d._x;
		_y *= point3d._y;
		_z *= point3d._z;

		return *this;
	}

	Point3D Point3D::operator*=(const float operation)
	{
		_x *= operation;
		_y *= operation;
		_z *= operation;

		return *this;
	}

	Point3D Point3D::operator/=(const Point3D& point3d)
	{
		_x /= point3d._x;
		_y /= point3d._y;
		_z /= point3d._z;

		return *this;
	}

	Point3D Point3D::operator/=(const float operation)
	{
		_x /= operation;
		_y /= operation;
		_z /= operation;

		return *this;
	}

	void Point3D::set(const Point3D& point3d)
	{
		_x = point3d._x;
		_y = point3d._y;
		_z = point3d._z;
	}

	void Point3D::set(const float x, const float y, const float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	void Point3D::set(const int x, const int y, const int z)
	{
		_x = static_cast<float>(x);
		_y = static_cast<float>(y);
		_z = static_cast<float>(z);
	}

	void Point3D::setX(const float x)
	{
		_x = x;
	}

	void Point3D::setX(const int x)
	{
		_x = static_cast<float>(x);
	}

	void Point3D::setY(const float y)
	{
		_y = y;
	}

	void Point3D::setY(const int y)
	{
		_y = static_cast<float>(y);
	}

	void Point3D::setZ(const float z)
	{
		_z = z;
	}

	void Point3D::setZ(const int z)
	{
		_z = static_cast<float>(z);
	}
}
