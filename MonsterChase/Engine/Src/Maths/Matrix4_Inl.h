#pragma once
#include "Point3D.h"
#include "Point4D.h"

#include <iostream>

namespace Math
{
#pragma region Static Operations

	inline Matrix4 operator*(const Matrix4& i_matrix4_1, const Matrix4& i_matrix4_2)
	{
		Matrix4 matrix4 = Matrix4();

		matrix4._tempMatrix[Matrix4::M00] = i_matrix4_1._matrixData[Matrix4::M00] * i_matrix4_2._matrixData[Matrix4::M00
			] + i_matrix4_1._matrixData[
				Matrix4::M01] *
			i_matrix4_2._matrixData[Matrix4::M10] +
			i_matrix4_1._matrixData[Matrix4::M02] * i_matrix4_2._matrixData[Matrix4::M20] + i_matrix4_1._matrixData[
				Matrix4::M03] * i_matrix4_2.
			_matrixData[Matrix4::M30];
		matrix4._tempMatrix[Matrix4::M01] = i_matrix4_1._matrixData[Matrix4::M00] * i_matrix4_2._matrixData[Matrix4::M01
			] + i_matrix4_1._matrixData[
				Matrix4::M01] *
			i_matrix4_2._matrixData[Matrix4::M11] +
			i_matrix4_1._matrixData[Matrix4::M02] * i_matrix4_2._matrixData[Matrix4::M21] + i_matrix4_1._matrixData[
				Matrix4::M03] * i_matrix4_2.
			_matrixData[Matrix4::M31];
		matrix4._tempMatrix[Matrix4::M02] = i_matrix4_1._matrixData[Matrix4::M00] * i_matrix4_2._matrixData[Matrix4::M02
			] + i_matrix4_1._matrixData[
				Matrix4::M01] *
			i_matrix4_2._matrixData[Matrix4::M12] +
			i_matrix4_1._matrixData[Matrix4::M02] * i_matrix4_2._matrixData[Matrix4::M22] + i_matrix4_1._matrixData[
				Matrix4::M03] * i_matrix4_2.
			_matrixData[Matrix4::M32];
		matrix4._tempMatrix[Matrix4::M03] = i_matrix4_1._matrixData[Matrix4::M00] * i_matrix4_2._matrixData[Matrix4::M03
			] + i_matrix4_1._matrixData[
				Matrix4::M01] *
			i_matrix4_2._matrixData[Matrix4::M13] +
			i_matrix4_1._matrixData[Matrix4::M02] * i_matrix4_2._matrixData[Matrix4::M23] + i_matrix4_1._matrixData[
				Matrix4::M03] * i_matrix4_2.
			_matrixData[Matrix4::M33];
		matrix4._tempMatrix[Matrix4::M10] = i_matrix4_1._matrixData[Matrix4::M10] * i_matrix4_2._matrixData[Matrix4::M00
			] + i_matrix4_1._matrixData[
				Matrix4::M11] *
			i_matrix4_2._matrixData[Matrix4::M10] +
			i_matrix4_1._matrixData[Matrix4::M12] * i_matrix4_2._matrixData[Matrix4::M20] + i_matrix4_1._matrixData[
				Matrix4::M13] * i_matrix4_2.
			_matrixData[Matrix4::M30];
		matrix4._tempMatrix[Matrix4::M11] = i_matrix4_1._matrixData[Matrix4::M10] * i_matrix4_2._matrixData[Matrix4::M01
			] + i_matrix4_1._matrixData[
				Matrix4::M11] *
			i_matrix4_2._matrixData[Matrix4::M11] +
			i_matrix4_1._matrixData[Matrix4::M12] * i_matrix4_2._matrixData[Matrix4::M21] + i_matrix4_1._matrixData[
				Matrix4::M13] * i_matrix4_2.
			_matrixData[Matrix4::M31];
		matrix4._tempMatrix[Matrix4::M12] = i_matrix4_1._matrixData[Matrix4::M10] * i_matrix4_2._matrixData[Matrix4::M02
			] + i_matrix4_1._matrixData[
				Matrix4::M11] *
			i_matrix4_2._matrixData[Matrix4::M12] +
			i_matrix4_1._matrixData[Matrix4::M12] * i_matrix4_2._matrixData[Matrix4::M22] + i_matrix4_1._matrixData[
				Matrix4::M13] * i_matrix4_2.
			_matrixData[Matrix4::M32];
		matrix4._tempMatrix[Matrix4::M13] = i_matrix4_1._matrixData[Matrix4::M10] * i_matrix4_2._matrixData[Matrix4::M03
			] + i_matrix4_1._matrixData[
				Matrix4::M11] *
			i_matrix4_2._matrixData[Matrix4::M13] +
			i_matrix4_1._matrixData[Matrix4::M12] * i_matrix4_2._matrixData[Matrix4::M23] + i_matrix4_1._matrixData[
				Matrix4::M13] * i_matrix4_2.
			_matrixData[Matrix4::M33];
		matrix4._tempMatrix[Matrix4::M20] = i_matrix4_1._matrixData[Matrix4::M20] * i_matrix4_2._matrixData[Matrix4::M00
			] + i_matrix4_1._matrixData[
				Matrix4::M21] *
			i_matrix4_2._matrixData[Matrix4::M10] +
			i_matrix4_1._matrixData[Matrix4::M22] * i_matrix4_2._matrixData[Matrix4::M20] + i_matrix4_1._matrixData[
				Matrix4::M23] * i_matrix4_2.
			_matrixData[Matrix4::M30];
		matrix4._tempMatrix[Matrix4::M21] = i_matrix4_1._matrixData[Matrix4::M20] * i_matrix4_2._matrixData[Matrix4::M01
			] + i_matrix4_1._matrixData[
				Matrix4::M21] *
			i_matrix4_2._matrixData[Matrix4::M11] +
			i_matrix4_1._matrixData[Matrix4::M22] * i_matrix4_2._matrixData[Matrix4::M21] + i_matrix4_1._matrixData[
				Matrix4::M23] * i_matrix4_2.
			_matrixData[Matrix4::M31];
		matrix4._tempMatrix[Matrix4::M22] = i_matrix4_1._matrixData[Matrix4::M20] * i_matrix4_2._matrixData[Matrix4::M02
			] + i_matrix4_1._matrixData[
				Matrix4::M21] *
			i_matrix4_2._matrixData[Matrix4::M12] +
			i_matrix4_1._matrixData[Matrix4::M22] * i_matrix4_2._matrixData[Matrix4::M22] + i_matrix4_1._matrixData[
				Matrix4::M23] * i_matrix4_2.
			_matrixData[Matrix4::M32];
		matrix4._tempMatrix[Matrix4::M23] = i_matrix4_1._matrixData[Matrix4::M20] * i_matrix4_2._matrixData[Matrix4::M03
			] + i_matrix4_1._matrixData[
				Matrix4::M21] *
			i_matrix4_2._matrixData[Matrix4::M13] +
			i_matrix4_1._matrixData[Matrix4::M22] * i_matrix4_2._matrixData[Matrix4::M23] + i_matrix4_1._matrixData[
				Matrix4::M23] * i_matrix4_2.
			_matrixData[Matrix4::M33];
		matrix4._tempMatrix[Matrix4::M30] = i_matrix4_1._matrixData[Matrix4::M30] * i_matrix4_2._matrixData[Matrix4::M00
			] + i_matrix4_1._matrixData[
				Matrix4::M31] *
			i_matrix4_2._matrixData[Matrix4::M10] +
			i_matrix4_1._matrixData[Matrix4::M32] * i_matrix4_2._matrixData[Matrix4::M20] + i_matrix4_1._matrixData[
				Matrix4::M33]
			* i_matrix4_2.
			_matrixData[Matrix4::M30];
		matrix4._tempMatrix[Matrix4::M31] = i_matrix4_1._matrixData[Matrix4::M30] * i_matrix4_2._matrixData[Matrix4::M01
			] + i_matrix4_1._matrixData[
				Matrix4::M31] *
			i_matrix4_2._matrixData[Matrix4::M11] +
			i_matrix4_1._matrixData[Matrix4::M32] * i_matrix4_2._matrixData[Matrix4::M21] + i_matrix4_1._matrixData[
				Matrix4::M33]
			* i_matrix4_2.
			_matrixData[Matrix4::M31];
		matrix4._tempMatrix[Matrix4::M32] = i_matrix4_1._matrixData[Matrix4::M30] * i_matrix4_2._matrixData[Matrix4::M02
			] + i_matrix4_1._matrixData[
				Matrix4::M31] *
			i_matrix4_2._matrixData[Matrix4::M12] +
			i_matrix4_1._matrixData[Matrix4::M32] * i_matrix4_2._matrixData[Matrix4::M22] + i_matrix4_1._matrixData[
				Matrix4::M33]
			* i_matrix4_2.
			_matrixData[Matrix4::M32];
		matrix4._tempMatrix[Matrix4::M33] = i_matrix4_1._matrixData[Matrix4::M30] * i_matrix4_2._matrixData[Matrix4::M03
			] +
			i_matrix4_1._matrixData[Matrix4::M31] *
			i_matrix4_2._matrixData[Matrix4::M13] +
			i_matrix4_1._matrixData[Matrix4::M32] * i_matrix4_2._matrixData[Matrix4::M23] + i_matrix4_1._matrixData[
				Matrix4::M33] * i_matrix4_2._matrixData[Matrix4::M33];

		for (size_t i = 0; i < matrix4._matrixData.size(); i++)
		{
			matrix4._matrixData[i] = matrix4._tempMatrix[i];
		}

		return matrix4;
	}

	inline Point3D operator*(const Matrix4& i_matrix4_2, const Point3D& i_point3d)
	{
		const float x = i_point3d.X() * i_matrix4_2._matrixData[Matrix4::M00] + i_point3d.Y() *
			i_matrix4_2._matrixData[Matrix4::M01] + i_point3d.Z()
			* i_matrix4_2._matrixData[Matrix4::M02] + i_matrix4_2._matrixData[Matrix4::M03];
		const float y = i_point3d.X() * i_matrix4_2._matrixData[Matrix4::M10] + i_point3d.Y() *
			i_matrix4_2._matrixData[Matrix4::M11] + i_point3d.Z()
			* i_matrix4_2._matrixData[Matrix4::M12] + i_matrix4_2._matrixData[Matrix4::M13];
		const float z = i_point3d.X() * i_matrix4_2._matrixData[Matrix4::M20] + i_point3d.Y() *
			i_matrix4_2._matrixData[Matrix4::M21] + i_point3d.Z()
			* i_matrix4_2._matrixData[Matrix4::M22] + i_matrix4_2._matrixData[Matrix4::M23];

		return Point3D(x, y, z);
	}

	inline Point4D operator*(const Matrix4& i_matrix4_2, const Point4D& i_point4d)
	{
		const float x = i_point4d.X() * i_matrix4_2._matrixData[Matrix4::M00] + i_point4d.Y() *
			i_matrix4_2._matrixData[Matrix4::M01] + i_point4d.Z()
			* i_matrix4_2._matrixData[Matrix4::M02] + i_point4d.W() * i_matrix4_2._matrixData[Matrix4::M03];
		const float y = i_point4d.X() * i_matrix4_2._matrixData[Matrix4::M10] + i_point4d.Y() *
			i_matrix4_2._matrixData[Matrix4::M11] + i_point4d.Z()
			* i_matrix4_2._matrixData[Matrix4::M12] + i_point4d.W() * i_matrix4_2._matrixData[Matrix4::M13];
		const float z = i_point4d.X() * i_matrix4_2._matrixData[Matrix4::M20] + i_point4d.Y() *
			i_matrix4_2._matrixData[Matrix4::M21] + i_point4d.Z()
			* i_matrix4_2._matrixData[Matrix4::M22] + i_point4d.W() * i_matrix4_2._matrixData[Matrix4::M23];
		const float w = i_point4d.X() * i_matrix4_2._matrixData[Matrix4::M30] + i_point4d.Y() *
			i_matrix4_2._matrixData[Matrix4::M31] + i_point4d.Z()
			* i_matrix4_2._matrixData[Matrix4::M32] + i_point4d.W() * i_matrix4_2._matrixData[Matrix4::M33];

		return Point4D(x, y, z, w);
	}

#pragma endregion

#pragma region Utility Functions

	inline std::ostream& operator<<(std::ostream& i_stream, const Matrix4& i_matrix4_2)
	{
		i_stream << "[" << i_matrix4_2._matrixData[Matrix4::M00] << "|" << i_matrix4_2._matrixData[Matrix4::M01] << "|"
			<<
			i_matrix4_2._matrixData[Matrix4::M02] << "|" << i_matrix4_2._matrixData[Matrix4::M03] <<
			"]\n" << "[" << i_matrix4_2._matrixData[Matrix4::M10] << "|" << i_matrix4_2._matrixData[Matrix4::M11] << "|"
			<< i_matrix4_2._matrixData[Matrix4::M12] << "|" << i_matrix4_2._matrixData[Matrix4::M13] << "]\n" << "[" <<
			i_matrix4_2._matrixData[Matrix4::M20] << "|" << i_matrix4_2._matrixData[Matrix4::M21] <<
			"|" << i_matrix4_2._matrixData[Matrix4::M22] << "|" << i_matrix4_2._matrixData[Matrix4::M23] << "]\n" << "["
			<< i_matrix4_2._matrixData[Matrix4::M30] << "|" << i_matrix4_2._matrixData[Matrix4::M31] << "|" <<
			i_matrix4_2.
			_matrixData[Matrix4::M32] << "|" << i_matrix4_2._matrixData[Matrix4::M33] << "]\n";

		return i_stream;
	}

	inline Matrix4 Matrix4::lerp(Matrix4& i_matrix4_1, const Matrix4& i_matrix4_2, const float i_alpha)
	{
		Matrix4 matrix;
		for (int i = 0; i < 16; i++)
		{
			matrix._matrixData[i] = i_matrix4_1._matrixData[i] * (1 - i_alpha) +
				i_matrix4_2._matrixData[i] * i_alpha;
		}

		return matrix;
	}

#pragma endregion
}
