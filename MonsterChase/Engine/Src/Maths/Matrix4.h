#pragma once
#include <array>
#include <ostream>

namespace Math
{
	class Point2D;
	class Point3D;
	class Point4D;

	// As of now only Column Vector functions exist
	// Will add Row Vectors is required later on...
	class Matrix4
	{
	private:
		static const int M00 = 0;
		static const int M10 = 1;
		static const int M20 = 2;
		static const int M30 = 3;
		static const int M01 = 4;
		static const int M11 = 5;
		static const int M21 = 6;
		static const int M31 = 7;
		static const int M02 = 8;
		static const int M12 = 9;
		static const int M22 = 10;
		static const int M32 = 11;
		static const int M03 = 12;
		static const int M13 = 13;
		static const int M23 = 14;
		static const int M33 = 15;

		static const size_t TotalElements = 16;
		std::array<float, TotalElements> _matrixData{};
		std::array<float, TotalElements> _tempMatrix{}; // This is only used for some calculations. Not really required

	public:

		// Constructor/Destructor
		Matrix4();
		Matrix4(float i_m00, float i_m01, float i_m02, float i_m03,
		        float i_m10, float i_m11, float i_m12, float i_m13,
		        float i_m20, float i_m21, float i_m22, float i_m23,
		        float i_m30, float i_m31, float i_m32, float i_m33);
		Matrix4(const float i_values[]);
		Matrix4(std::array<float, TotalElements>& i_values);
		Matrix4& operator=(const Matrix4& i_matrix4);
		~Matrix4() = default;

		// Static Operations
		inline friend Matrix4 operator*(const Matrix4& i_matrix4_1, const Matrix4& i_matrix4_2);
		inline friend Point3D operator*(const Matrix4& i_matrix4, const Point3D& i_point3d);
		inline friend Point4D operator*(const Matrix4& i_matrix4, const Point4D& i_point4d);

		// Getters
		[[nodiscard]] std::array<float, TotalElements> GetMatrix() const;
		void Inverse();
		float Determinant();
		float Determinant3x3(); // Determinant of Upper Left 3x3 matrix. For Translation and Scale
		Matrix4 Transpose();
		void Identity();

		// Utility Methods
		static Matrix4 CreateTranslationCV(Point2D& i_point2d);
		static Matrix4 CreateTranslationCV(Point3D& i_point3d);
		static Matrix4 CreateXRotationCV(float i_xRotRad);
		static Matrix4 CreateYRotationCV(float i_yRotRad);
		static Matrix4 CreateZRotationCV(const float i_zRotRad);
		static Matrix4 CreateScale(Point3D& i_point3d);
		Point3D TransformPoint(const Point3D& i_point3d) const;
		Point4D GetColVector4(size_t i_col);
		Point3D GetColVector3(size_t i_col);
		inline friend std::ostream& operator<<(std::ostream& i_stream, const Matrix4& i_matrix4);
		inline static Matrix4 lerp(Matrix4& i_matrix4_1, const Matrix4& i_matrix4_2, const float i_alpha);
	};
}

#include "Matrix4_Inl.h"
