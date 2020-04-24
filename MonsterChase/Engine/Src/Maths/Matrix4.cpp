#include "Matrix4.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Point4D.h"
#include "../Utils/MathUtils.h"

#include <cassert>
#include <cmath>

namespace Math
{
#pragma region Constructor and Destructor

	Matrix4::Matrix4()
	{
		for (size_t i = 0; i < Matrix4::TotalElements; i++)
		{
			this->_matrixData[i] = 0;
		}
	}

	Matrix4::Matrix4(const float i_m00, const float i_m01, const float i_m02, const float i_m03,
	                 const float i_m10, const float i_m11, const float i_m12, const float i_m13,
	                 const float i_m20, const float i_m21, const float i_m22, const float i_m23,
	                 const float i_m30, const float i_m31, const float i_m32, const float i_m33)
	{
		this->_matrixData[M00] = i_m00;
		this->_matrixData[M01] = i_m01;
		this->_matrixData[M02] = i_m02;
		this->_matrixData[M03] = i_m03;

		this->_matrixData[M10] = i_m10;
		this->_matrixData[M11] = i_m11;
		this->_matrixData[M12] = i_m12;
		this->_matrixData[M13] = i_m13;

		this->_matrixData[M20] = i_m20;
		this->_matrixData[M21] = i_m21;
		this->_matrixData[M22] = i_m22;
		this->_matrixData[M23] = i_m23;

		this->_matrixData[M30] = i_m30;
		this->_matrixData[M31] = i_m31;
		this->_matrixData[M32] = i_m32;
		this->_matrixData[M33] = i_m33;
	}

	Matrix4::Matrix4(const float i_values[])
	{
		for (size_t i = 0; i < Matrix4::TotalElements; i++)
		{
			this->_matrixData[i] = i_values[i];
		}
	}

	Matrix4::Matrix4(std::array<float, TotalElements>& i_values)
	{
		for (size_t i = 0; i < Matrix4::TotalElements; i++)
		{
			this->_matrixData[i] = i_values[i];
		}
	}

	Matrix4& Matrix4::operator=(const Matrix4& i_matrix4)
	{
		if (&i_matrix4 == this)
		{
			return *this;
		}

		_matrixData[M00] = i_matrix4._matrixData[M00];
		_matrixData[M01] = i_matrix4._matrixData[M01];
		_matrixData[M02] = i_matrix4._matrixData[M02];
		_matrixData[M03] = i_matrix4._matrixData[M03];
		_matrixData[M10] = i_matrix4._matrixData[M10];
		_matrixData[M11] = i_matrix4._matrixData[M11];
		_matrixData[M12] = i_matrix4._matrixData[M12];
		_matrixData[M13] = i_matrix4._matrixData[M13];
		_matrixData[M20] = i_matrix4._matrixData[M20];
		_matrixData[M21] = i_matrix4._matrixData[M21];
		_matrixData[M22] = i_matrix4._matrixData[M22];
		_matrixData[M23] = i_matrix4._matrixData[M23];
		_matrixData[M30] = i_matrix4._matrixData[M30];
		_matrixData[M31] = i_matrix4._matrixData[M31];
		_matrixData[M32] = i_matrix4._matrixData[M32];
		_matrixData[M33] = i_matrix4._matrixData[M33];

		return *this;
	}


#pragma endregion

#pragma region Getters

	std::array<float, Matrix4::TotalElements> Matrix4::GetMatrix() const
	{
		return this->_matrixData;
	}

	void Matrix4::Inverse()
	{
		const float det = this->_matrixData[M30] * this->_matrixData[M21] * this->_matrixData[M12]
			* this->_matrixData[M03]
			- this->_matrixData[M20] * this->_matrixData[M31] * this->_matrixData[M12] * this->_matrixData[M03] - this->
			_matrixData[M30] * this->_matrixData[M11]
			* this->_matrixData[M22] * this->_matrixData[M03] + this->_matrixData[M10] * this->_matrixData[M31] * this->
			_matrixData[M22] * this->_matrixData[M03] + this->_matrixData[M20] * this->_matrixData[M11] * this->
			_matrixData[M32] * this->_matrixData[M03] - this->_matrixData[M10]
			* this->_matrixData[M21] * this->_matrixData[M32] * this->_matrixData[M03] - this->_matrixData[M30] * this->
			_matrixData[M21] * this->_matrixData[M02] * this->_matrixData[M13] + this->_matrixData[M20] * this->
			_matrixData[M31] * this->_matrixData[M02] * this->_matrixData[M13]
			+ this->_matrixData[M30] * this->_matrixData[M01] * this->_matrixData[M22] * this->_matrixData[M13] - this->
			_matrixData[M00] * this->_matrixData[M31] * this->_matrixData[M22] * this->_matrixData[M13] - this->
			_matrixData[M20] * this->_matrixData[M01] * this->_matrixData[M32]
			* this->_matrixData[M13] + this->_matrixData[M00] * this->_matrixData[M21] * this->_matrixData[M32] * this->
			_matrixData[M13] + this->_matrixData[M30] * this->_matrixData[M11] * this->_matrixData[M02] * this->
			_matrixData[M23] - this->_matrixData[M10] * this->_matrixData[M31]
			* this->_matrixData[M02] * this->_matrixData[M23] - this->_matrixData[M30] * this->_matrixData[M01] * this->
			_matrixData[M12] * this->_matrixData[M23] + this->_matrixData[M00] * this->_matrixData[M31] * this->
			_matrixData[M12] * this->_matrixData[M23] + this->_matrixData[M10]
			* this->_matrixData[M01] * this->_matrixData[M32] * this->_matrixData[M23] - this->_matrixData[M00] * this->
			_matrixData[M11] * this->_matrixData[M32] * this->_matrixData[M23] - this->_matrixData[M20] * this->
			_matrixData[M11] * this->_matrixData[M02] * this->_matrixData[M33]
			+ this->_matrixData[M10] * this->_matrixData[M21] * this->_matrixData[M02] * this->_matrixData[M33] + this->
			_matrixData[M20] * this->_matrixData[M01] * this->_matrixData[M12] * this->_matrixData[M33] - this->
			_matrixData[M00] * this->_matrixData[M21] * this->_matrixData[M12]
			* this->_matrixData[M33] - this->_matrixData[M10] * this->_matrixData[M01] * this->_matrixData[M22] * this->
			_matrixData[M33] + this->_matrixData[M00] * this->_matrixData[M11] * this->_matrixData[M22] * this->
			_matrixData[M33];

		assert(det != 0);
		const float invDet = 1.0f / det;

		this->_tempMatrix[M00] = this->_matrixData[M12] * this->_matrixData[M23] * this->_matrixData[M31] - this->
			_matrixData[M13] * this->_matrixData[M22] * this->_matrixData[M31] + this->_matrixData[M13] * this->
			_matrixData[M21] * this->_matrixData[M32] - this->_matrixData[M11]
			* this->_matrixData[M23] * this->_matrixData[M32] - this->_matrixData[M12] * this->_matrixData[M21] * this->
			_matrixData[M33] + this->_matrixData[M11] * this->_matrixData[M22] * this->_matrixData[M33];
		this->_tempMatrix[M01] = this->_matrixData[M03] * this->_matrixData[M22] * this->_matrixData[M31] - this->
			_matrixData[M02] * this->_matrixData[M23] * this->_matrixData[M31] - this->_matrixData[M03] * this->
			_matrixData[M21] * this->_matrixData[M32] + this->_matrixData[M01]
			* this->_matrixData[M23] * this->_matrixData[M32] + this->_matrixData[M02] * this->_matrixData[M21] * this->
			_matrixData[M33] - this->_matrixData[M01] * this->_matrixData[M22] * this->_matrixData[M33];
		this->_tempMatrix[M02] = this->_matrixData[M02] * this->_matrixData[M13] * this->_matrixData[M31] - this->
			_matrixData[M03] * this->_matrixData[M12] * this->_matrixData[M31] + this->_matrixData[M03] * this->
			_matrixData[M11] * this->_matrixData[M32] - this->_matrixData[M01]
			* this->_matrixData[M13] * this->_matrixData[M32] - this->_matrixData[M02] * this->_matrixData[M11] * this->
			_matrixData[M33] + this->_matrixData[M01] * this->_matrixData[M12] * this->_matrixData[M33];
		this->_tempMatrix[M03] = this->_matrixData[M03] * this->_matrixData[M12] * this->_matrixData[M21] - this->
			_matrixData[M02] * this->_matrixData[M13] * this->_matrixData[M21] - this->_matrixData[M03] * this->
			_matrixData[M11] * this->_matrixData[M22] + this->_matrixData[M01]
			* this->_matrixData[M13] * this->_matrixData[M22] + this->_matrixData[M02] * this->_matrixData[M11] * this->
			_matrixData[M23] - this->_matrixData[M01] * this->_matrixData[M12] * this->_matrixData[M23];
		this->_tempMatrix[M10] = this->_matrixData[M13] * this->_matrixData[M22] * this->_matrixData[M30] - this->
			_matrixData[M12] * this->_matrixData[M23] * this->_matrixData[M30] - this->_matrixData[M13] * this->
			_matrixData[M20] * this->_matrixData[M32] + this->_matrixData[M10]
			* this->_matrixData[M23] * this->_matrixData[M32] + this->_matrixData[M12] * this->_matrixData[M20] * this->
			_matrixData[M33] - this->_matrixData[M10] * this->_matrixData[M22] * this->_matrixData[M33];
		this->_tempMatrix[M11] = this->_matrixData[M02] * this->_matrixData[M23] * this->_matrixData[M30] - this->
			_matrixData[M03] * this->_matrixData[M22] * this->_matrixData[M30] + this->_matrixData[M03] * this->
			_matrixData[M20] * this->_matrixData[M32] - this->_matrixData[M00]
			* this->_matrixData[M23] * this->_matrixData[M32] - this->_matrixData[M02] * this->_matrixData[M20] * this->
			_matrixData[M33] + this->_matrixData[M00] * this->_matrixData[M22] * this->_matrixData[M33];
		this->_tempMatrix[M12] = this->_matrixData[M03] * this->_matrixData[M12] * this->_matrixData[M30] - this->
			_matrixData[M02] * this->_matrixData[M13] * this->_matrixData[M30] - this->_matrixData[M03] * this->
			_matrixData[M10] * this->_matrixData[M32] + this->_matrixData[M00]
			* this->_matrixData[M13] * this->_matrixData[M32] + this->_matrixData[M02] * this->_matrixData[M10] * this->
			_matrixData[M33] - this->_matrixData[M00] * this->_matrixData[M12] * this->_matrixData[M33];
		this->_tempMatrix[M13] = this->_matrixData[M02] * this->_matrixData[M13] * this->_matrixData[M20] - this->
			_matrixData[M03] * this->_matrixData[M12] * this->_matrixData[M20] + this->_matrixData[M03] * this->
			_matrixData[M10] * this->_matrixData[M22] - this->_matrixData[M00]
			* this->_matrixData[M13] * this->_matrixData[M22] - this->_matrixData[M02] * this->_matrixData[M10] * this->
			_matrixData[M23] + this->_matrixData[M00] * this->_matrixData[M12] * this->_matrixData[M23];
		this->_tempMatrix[M20] = this->_matrixData[M11] * this->_matrixData[M23] * this->_matrixData[M30] - this->
			_matrixData[M13] * this->_matrixData[M21] * this->_matrixData[M30] + this->_matrixData[M13] * this->
			_matrixData[M20] * this->_matrixData[M31] - this->_matrixData[M10]
			* this->_matrixData[M23] * this->_matrixData[M31] - this->_matrixData[M11] * this->_matrixData[M20] * this->
			_matrixData[M33] + this->_matrixData[M10] * this->_matrixData[M21] * this->_matrixData[M33];
		this->_tempMatrix[M21] = this->_matrixData[M03] * this->_matrixData[M21] * this->_matrixData[M30] - this->
			_matrixData[M01] * this->_matrixData[M23] * this->_matrixData[M30] - this->_matrixData[M03] * this->
			_matrixData[M20] * this->_matrixData[M31] + this->_matrixData[M00]
			* this->_matrixData[M23] * this->_matrixData[M31] + this->_matrixData[M01] * this->_matrixData[M20] * this->
			_matrixData[M33] - this->_matrixData[M00] * this->_matrixData[M21] * this->_matrixData[M33];
		this->_tempMatrix[M22] = this->_matrixData[M01] * this->_matrixData[M13] * this->_matrixData[M30] - this->
			_matrixData[M03] * this->_matrixData[M11] * this->_matrixData[M30] + this->_matrixData[M03] * this->
			_matrixData[M10] * this->_matrixData[M31] - this->_matrixData[M00]
			* this->_matrixData[M13] * this->_matrixData[M31] - this->_matrixData[M01] * this->_matrixData[M10] * this->
			_matrixData[M33] + this->_matrixData[M00] * this->_matrixData[M11] * this->_matrixData[M33];
		this->_tempMatrix[M23] = this->_matrixData[M03] * this->_matrixData[M11] * this->_matrixData[M20] - this->
			_matrixData[M01] * this->_matrixData[M13] * this->_matrixData[M20] - this->_matrixData[M03] * this->
			_matrixData[M10] * this->_matrixData[M21] + this->_matrixData[M00]
			* this->_matrixData[M13] * this->_matrixData[M21] + this->_matrixData[M01] * this->_matrixData[M10] * this->
			_matrixData[M23] - this->_matrixData[M00] * this->_matrixData[M11] * this->_matrixData[M23];
		this->_tempMatrix[M30] = this->_matrixData[M12] * this->_matrixData[M21] * this->_matrixData[M30] - this->
			_matrixData[M11] * this->_matrixData[M22] * this->_matrixData[M30] - this->_matrixData[M12] * this->
			_matrixData[M20] * this->_matrixData[M31] + this->_matrixData[M10]
			* this->_matrixData[M22] * this->_matrixData[M31] + this->_matrixData[M11] * this->_matrixData[M20] * this->
			_matrixData[M32] - this->_matrixData[M10] * this->_matrixData[M21] * this->_matrixData[M32];
		this->_tempMatrix[M31] = this->_matrixData[M01] * this->_matrixData[M22] * this->_matrixData[M30] - this->
			_matrixData[M02] * this->_matrixData[M21] * this->_matrixData[M30] + this->_matrixData[M02] * this->
			_matrixData[M20] * this->_matrixData[M31] - this->_matrixData[M00]
			* this->_matrixData[M22] * this->_matrixData[M31] - this->_matrixData[M01] * this->_matrixData[M20] * this->
			_matrixData[M32] + this->_matrixData[M00] * this->_matrixData[M21] * this->_matrixData[M32];
		this->_tempMatrix[M32] = this->_matrixData[M02] * this->_matrixData[M11] * this->_matrixData[M30] - this->
			_matrixData[M01] * this->_matrixData[M12] * this->_matrixData[M30] - this->_matrixData[M02] * this->
			_matrixData[M10] * this->_matrixData[M31] + this->_matrixData[M00]
			* this->_matrixData[M12] * this->_matrixData[M31] + this->_matrixData[M01] * this->_matrixData[M10] * this->
			_matrixData[M32] - this->_matrixData[M00] * this->_matrixData[M11] * this->_matrixData[M32];
		this->_tempMatrix[M33] = this->_matrixData[M01] * this->_matrixData[M12] * this->_matrixData[M20] - this->
			_matrixData[M02] * this->_matrixData[M11] * this->_matrixData[M20] + this->_matrixData[M02] * this->
			_matrixData[M10] * this->_matrixData[M21] - this->_matrixData[M00]
			* this->_matrixData[M12] * this->_matrixData[M21] - this->_matrixData[M01] * this->_matrixData[M10] * this->
			_matrixData[M22] + this->_matrixData[M00] * this->_matrixData[M11] * this->_matrixData[M22];

		this->_matrixData[M00] = this->_tempMatrix[M00] * invDet;
		this->_matrixData[M01] = this->_tempMatrix[M01] * invDet;
		this->_matrixData[M02] = this->_tempMatrix[M02] * invDet;
		this->_matrixData[M03] = this->_tempMatrix[M03] * invDet;
		this->_matrixData[M10] = this->_tempMatrix[M10] * invDet;
		this->_matrixData[M11] = this->_tempMatrix[M11] * invDet;
		this->_matrixData[M12] = this->_tempMatrix[M12] * invDet;
		this->_matrixData[M13] = this->_tempMatrix[M13] * invDet;
		this->_matrixData[M20] = this->_tempMatrix[M20] * invDet;
		this->_matrixData[M21] = this->_tempMatrix[M21] * invDet;
		this->_matrixData[M22] = this->_tempMatrix[M22] * invDet;
		this->_matrixData[M23] = this->_tempMatrix[M23] * invDet;
		this->_matrixData[M30] = this->_tempMatrix[M30] * invDet;
		this->_matrixData[M31] = this->_tempMatrix[M31] * invDet;
		this->_matrixData[M32] = this->_tempMatrix[M32] * invDet;
		this->_matrixData[M33] = this->_tempMatrix[M33] * invDet;
	}

	float Matrix4::Determinant()
	{
		return this->_matrixData[M30] * this->_matrixData[M21] * this->_matrixData[M12] * this->_matrixData[M03] - this
			->_matrixData[M20] * this->_matrixData[M31] * this->_matrixData[M12] * this->_matrixData[M03] - this->
			_matrixData[M30] * this->_matrixData[M11]
			* this->_matrixData[M22] * this->_matrixData[M03] + this->_matrixData[M10] * this->_matrixData[M31] * this->
			_matrixData[M22] * this->_matrixData[M03] + this->_matrixData[M20] * this->_matrixData[M11] * this->
			_matrixData[M32] * this->_matrixData[M03] - this->_matrixData[M10]
			* this->_matrixData[M21] * this->_matrixData[M32] * this->_matrixData[M03] - this->_matrixData[M30] * this->
			_matrixData[M21] * this->_matrixData[M02] * this->_matrixData[M13] + this->_matrixData[M20] * this->
			_matrixData[M31] * this->_matrixData[M02] * this->_matrixData[M13]
			+ this->_matrixData[M30] * this->_matrixData[M01] * this->_matrixData[M22] * this->_matrixData[M13] - this->
			_matrixData[M00] * this->_matrixData[M31] * this->_matrixData[M22] * this->_matrixData[M13] - this->
			_matrixData[M20] * this->_matrixData[M01] * this->_matrixData[M32]
			* this->_matrixData[M13] + this->_matrixData[M00] * this->_matrixData[M21] * this->_matrixData[M32] * this->
			_matrixData[M13] + this->_matrixData[M30] * this->_matrixData[M11] * this->_matrixData[M02] * this->
			_matrixData[M23] - this->_matrixData[M10] * this->_matrixData[M31]
			* this->_matrixData[M02] * this->_matrixData[M23] - this->_matrixData[M30] * this->_matrixData[M01] * this->
			_matrixData[M12] * this->_matrixData[M23] + this->_matrixData[M00] * this->_matrixData[M31] * this->
			_matrixData[M12] * this->_matrixData[M23] + this->_matrixData[M10]
			* this->_matrixData[M01] * this->_matrixData[M32] * this->_matrixData[M23] - this->_matrixData[M00] * this->
			_matrixData[M11] * this->_matrixData[M32] * this->_matrixData[M23] - this->_matrixData[M20] * this->
			_matrixData[M11] * this->_matrixData[M02] * this->_matrixData[M33]
			+ this->_matrixData[M10] * this->_matrixData[M21] * this->_matrixData[M02] * this->_matrixData[M33] + this->
			_matrixData[M20] * this->_matrixData[M01] * this->_matrixData[M12] * this->_matrixData[M33] - this->
			_matrixData[M00] * this->_matrixData[M21] * this->_matrixData[M12]
			* this->_matrixData[M33] - this->_matrixData[M10] * this->_matrixData[M01] * this->_matrixData[M22] * this->
			_matrixData[M33] + this->_matrixData[M00] * this->_matrixData[M11] * this->_matrixData[M22] * this->
			_matrixData[M33];
	}

	float Matrix4::Determinant3x3()
	{
		return this->_matrixData[M00] * this->_matrixData[M11] * this->_matrixData[M22] + this->_matrixData[M01] * this
			->_matrixData[M12] * this->_matrixData[M20] + this->_matrixData[M02] * this->_matrixData[M10] * this->
			_matrixData[M21] - this->_matrixData[M00]
			* this->_matrixData[M12] * this->_matrixData[M21] - this->_matrixData[M01] * this->_matrixData[M10] * this->
			_matrixData[M22] - this->_matrixData[M02] * this->_matrixData[M11] * this->_matrixData[M20];
	}

	Matrix4 Matrix4::Transpose()
	{
		this->_tempMatrix[M00] = this->_matrixData[M00];
		this->_tempMatrix[M01] = this->_matrixData[M10];
		this->_tempMatrix[M02] = this->_matrixData[M20];
		this->_tempMatrix[M03] = this->_matrixData[M30];
		this->_tempMatrix[M10] = this->_matrixData[M01];
		this->_tempMatrix[M11] = this->_matrixData[M11];
		this->_tempMatrix[M12] = this->_matrixData[M21];
		this->_tempMatrix[M13] = this->_matrixData[M31];
		this->_tempMatrix[M20] = this->_matrixData[M02];
		this->_tempMatrix[M21] = this->_matrixData[M12];
		this->_tempMatrix[M22] = this->_matrixData[M22];
		this->_tempMatrix[M23] = this->_matrixData[M32];
		this->_tempMatrix[M30] = this->_matrixData[M03];
		this->_tempMatrix[M31] = this->_matrixData[M13];
		this->_tempMatrix[M32] = this->_matrixData[M23];
		this->_tempMatrix[M33] = this->_matrixData[M33];

		for (size_t i = 0; i < Matrix4::TotalElements; i++)
		{
			this->_matrixData[i] = this->_tempMatrix[i];
		}

		return *this;
	}

	void Matrix4::Identity()
	{
		this->_matrixData[M00] = 1;
		this->_matrixData[M01] = 0;
		this->_matrixData[M02] = 0;
		this->_matrixData[M03] = 0;
		this->_matrixData[M10] = 0;
		this->_matrixData[M11] = 1;
		this->_matrixData[M12] = 0;
		this->_matrixData[M13] = 0;
		this->_matrixData[M20] = 0;
		this->_matrixData[M21] = 0;
		this->_matrixData[M22] = 1;
		this->_matrixData[M23] = 0;
		this->_matrixData[M30] = 0;
		this->_matrixData[M31] = 0;
		this->_matrixData[M32] = 0;
		this->_matrixData[M33] = 1;
	}

#pragma endregion

#pragma region Utility Methods

	Matrix4 Matrix4::CreateTranslationCV(Point2D& i_point2d)
	{
		Matrix4 matrix4 = Matrix4();
		matrix4.Identity();
		matrix4._matrixData[M03] = i_point2d.X();
		matrix4._matrixData[M13] = i_point2d.Y();
		matrix4._matrixData[M23] = 0;
		return matrix4;
	}

	Matrix4 Matrix4::CreateTranslationCV(Point3D& i_point3d)
	{
		Matrix4 matrix4;
		matrix4.Identity();
		matrix4._matrixData[M03] = i_point3d.X();
		matrix4._matrixData[M13] = i_point3d.Y();
		matrix4._matrixData[M23] = i_point3d.Z();
		return matrix4;
	}

	Matrix4 Matrix4::CreateXRotationCV(const float i_xRotRad)
	{
		const float sin = std::sinf(i_xRotRad);
		const float cos = std::cosf(i_xRotRad);

		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cos, -sin, 0.0f,
			0.0f, sin, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::CreateYRotationCV(const float i_yRotRad)
	{
		const float sin = std::sinf(i_yRotRad);
		const float cos = std::cosf(i_yRotRad);

		return Matrix4(
			cos, 0.0f, sin, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-sin, 0.0f, cos, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::CreateZRotationCV(const float i_zRotRad)
	{
		const float sin = std::sinf(i_zRotRad);
		const float cos = std::cosf(i_zRotRad);

		return Matrix4(
			cos, -sin, 0.0f, 0.0f,
			sin, cos, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4 Matrix4::CreateScale(Point3D& i_point3d)
	{
		Matrix4 matrix;

		matrix._matrixData[M00] = i_point3d.X();
		matrix._matrixData[M01] = 0;
		matrix._matrixData[M02] = 0;
		matrix._matrixData[M03] = 0;
		matrix._matrixData[M10] = 0;
		matrix._matrixData[M11] = i_point3d.Y();
		matrix._matrixData[M12] = 0;
		matrix._matrixData[M13] = 0;
		matrix._matrixData[M20] = 0;
		matrix._matrixData[M21] = 0;
		matrix._matrixData[M22] = i_point3d.Z();
		matrix._matrixData[M23] = 0;
		matrix._matrixData[M30] = 0;
		matrix._matrixData[M31] = 0;
		matrix._matrixData[M32] = 0;
		matrix._matrixData[M33] = 1;

		return matrix;
	}

	Point3D Matrix4::TransformPoint(const Point3D& i_point3d) const
	{
		const Point4D point4d = *this * Point4D(i_point3d, 1.0f);
		assert(!Utils::MathUtils::IsZero(point4d.W()));

		const float invW = 1.0f / point4d.W();
		return Point3D(point4d.X() * invW, point4d.Y() * invW, point4d.Z() * invW);
	}

	Point4D Matrix4::GetColVector4(const size_t i_col)
	{
		switch (i_col)
		{
		case 0:
			return Point4D(this->_matrixData[M00],
			               this->_matrixData[M10],
			               this->_matrixData[M20],
			               this->_matrixData[M30]
			);

		case 1:
			return Point4D(this->_matrixData[M01],
			               this->_matrixData[M11],
			               this->_matrixData[M21],
			               this->_matrixData[M31]
			);

		case 2:
			return Point4D(this->_matrixData[M02],
			               this->_matrixData[M12],
			               this->_matrixData[M22],
			               this->_matrixData[M32]
			);

		case 3:
			return Point4D(this->_matrixData[M03],
			               this->_matrixData[M13],
			               this->_matrixData[M23],
			               this->_matrixData[M33]
			);

		default:
			assert(false);
			return Point4D();
		}
	}

	Point3D Matrix4::GetColVector3(const size_t i_col)
	{
		switch (i_col)
		{
		case 0:
			return Point3D(this->_matrixData[M00],
			               this->_matrixData[M10],
			               this->_matrixData[M20]
			);

		case 1:
			return Point3D(this->_matrixData[M01],
			               this->_matrixData[M11],
			               this->_matrixData[M21]
			);

		case 2:
			return Point3D(this->_matrixData[M02],
			               this->_matrixData[M12],
			               this->_matrixData[M22]
			);

		default:
			assert(false);
			return Point3D();
		}
	}

#pragma endregion
}
