/*
*
*	Megan Grass
*	April 11, 2024
*
*
*	TODO:
*
*/


#pragma once

#include "std_vertex.h"


typedef class Standard_Matrix StdMat;


/*
	Standard Matrix 4x4
*/
class Standard_Matrix {
private:

public:

	/*
		Data
	*/
	float
		m00, m10, m20, m30,
		m01, m11, m21, m31,
		m02, m12, m22, m32,
		m03, m13, m23, m33;

	/*
		Construction
	*/
	explicit Standard_Matrix(void) noexcept :
		m00(1.0f), m10(0.0f), m20(0.0f), m30(0.0f),
		m01(0.0f), m11(1.0f), m21(0.0f), m31(0.0f),
		m02(0.0f), m12(0.0f), m22(1.0f), m32(0.0f),
		m03(0.0f), m13(0.0f), m23(0.0f), m33(1.0f) {}
	explicit Standard_Matrix(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33) noexcept :
		m00(_00), m10(_10), m20(_20), m30(_30),
		m01(_01), m11(_11), m21(_21), m31(_31),
		m02(_02), m12(_12), m22(_22), m32(_32),
		m03(_03), m13(_13), m23(_23), m33(_33) {}
	explicit Standard_Matrix(float tX, float tY, float tZ) noexcept :
		m00(1.0f), m10(0.0f), m20(0.0f), m30(0.0f),
		m01(0.0f), m11(1.0f), m21(0.0f), m31(0.0f),
		m02(0.0f), m12(0.0f), m22(1.0f), m32(0.0f),
		m03(tX), m13(tY), m23(tZ), m33(1.0f) {}
	explicit Standard_Matrix(Standard_Vertex tVertex) noexcept :
		m00(1.0f), m10(0.0f), m20(0.0f), m30(0.0f),
		m01(0.0f), m11(1.0f), m21(0.0f), m31(0.0f),
		m02(0.0f), m12(0.0f), m22(1.0f), m32(0.0f),
		m03(tVertex.x), m13(tVertex.y), m23(tVertex.z), m33(1.0f) {}

	/*
		Copy
	*/
	Standard_Matrix(const Standard_Matrix& m) noexcept :
		m00(m.m00), m10(m.m10), m20(m.m20), m30(m.m30),
		m01(m.m01), m11(m.m11), m21(m.m21), m31(m.m31),
		m02(m.m02), m12(m.m12), m22(m.m22), m32(m.m32),
		m03(m.m03), m13(m.m13), m23(m.m23), m33(m.m33) {}
	Standard_Matrix& operator = (const Standard_Matrix& m) noexcept { return *this = Standard_Matrix(m); }

	/*
		Move
	*/
	Standard_Matrix(Standard_Matrix&& m) noexcept :
		m00(std::exchange(m.m00, 0.0f)), m10(std::exchange(m.m10, 0.0f)), m20(std::exchange(m.m20, 0.0f)), m30(std::exchange(m.m30, 0.0f)),
		m01(std::exchange(m.m01, 0.0f)), m11(std::exchange(m.m11, 0.0f)), m21(std::exchange(m.m21, 0.0f)), m31(std::exchange(m.m31, 0.0f)),
		m02(std::exchange(m.m02, 0.0f)), m12(std::exchange(m.m12, 0.0f)), m22(std::exchange(m.m22, 0.0f)), m32(std::exchange(m.m32, 0.0f)),
		m03(std::exchange(m.m03, 0.0f)), m13(std::exchange(m.m13, 0.0f)), m23(std::exchange(m.m23, 0.0f)), m33(std::exchange(m.m33, 0.0f)) {}
	Standard_Matrix& operator = (Standard_Matrix&& m) noexcept
	{
		std::swap(m00, m.m00); std::swap(m10, m.m10); std::swap(m20, m.m20); std::swap(m30, m.m30);
		std::swap(m01, m.m01); std::swap(m11, m.m11); std::swap(m21, m.m21); std::swap(m31, m.m31);
		std::swap(m02, m.m02); std::swap(m12, m.m12); std::swap(m22, m.m22); std::swap(m32, m.m32);
		std::swap(m03, m.m03); std::swap(m13, m.m13); std::swap(m23, m.m23); std::swap(m33, m.m33);
		return *this;
	}

	/*
		Unary
	*/
	Standard_Matrix operator - (void) const noexcept
	{
		Standard_Matrix result;

		result.m00 = -m00;
		result.m01 = -m01;
		result.m02 = -m02;
		result.m03 = -m03;

		result.m10 = -m10;
		result.m11 = -m11;
		result.m12 = -m12;
		result.m13 = -m13;

		result.m20 = -m20;
		result.m21 = -m21;
		result.m22 = -m22;
		result.m23 = -m23;

		result.m30 = -m30;
		result.m31 = -m31;
		result.m32 = -m32;
		result.m33 = -m33;

		return result;
	}

	/*
		Equality
	*/
	bool operator == (const Standard_Matrix& m) const noexcept
	{
		return m00 == m.m00 && m10 == m.m10 && m20 == m.m20 && m30 == m.m30 &&
			m01 == m.m01 && m11 == m.m11 && m21 == m.m21 && m31 == m.m31 &&
			m02 == m.m02 && m12 == m.m12 && m22 == m.m22 && m32 == m.m32 &&
			m03 == m.m03 && m13 == m.m13 && m23 == m.m23 && m33 == m.m33;
	}
	bool operator != (const Standard_Matrix& m) const noexcept { return !(*this == m); }

	/*
		Addition
	*/
	Standard_Matrix operator + (const Standard_Matrix& m) const noexcept
	{
		Standard_Matrix result;

		result.m00 = m00 + m.m00;
		result.m01 = m01 + m.m01;
		result.m02 = m02 + m.m02;
		result.m03 = m03 + m.m03;

		result.m10 = m10 + m.m10;
		result.m11 = m11 + m.m11;
		result.m12 = m12 + m.m12;
		result.m13 = m13 + m.m13;

		result.m20 = m20 + m.m20;
		result.m21 = m21 + m.m21;
		result.m22 = m22 + m.m22;
		result.m23 = m23 + m.m23;

		result.m30 = m30 + m.m30;
		result.m31 = m31 + m.m31;
		result.m32 = m32 + m.m32;
		result.m33 = m33 + m.m33;

		return result;
	}
	Standard_Matrix& operator += (const Standard_Matrix& m) noexcept { return *this = *this + m; }

	/*
		Scalar Addition
	*/
	Standard_Matrix operator + (float s) const noexcept
	{
		Standard_Matrix result;

		result.m00 = m00 + s;
		result.m01 = m01 + s;
		result.m02 = m02 + s;
		result.m03 = m03 + s;

		result.m10 = m10 + s;
		result.m11 = m11 + s;
		result.m12 = m12 + s;
		result.m13 = m13 + s;

		result.m20 = m20 + s;
		result.m21 = m21 + s;
		result.m22 = m22 + s;
		result.m23 = m23 + s;

		result.m30 = m30 + s;
		result.m31 = m31 + s;
		result.m32 = m32 + s;
		result.m33 = m33 + s;

		return result;
	}
	Standard_Matrix& operator += (float s) noexcept { return *this = *this + s; }

	/*
		Subtraction
	*/
	Standard_Matrix operator - (const Standard_Matrix& m) const noexcept
	{
		Standard_Matrix result;

		result.m00 = m00 - m.m00;
		result.m01 = m01 - m.m01;
		result.m02 = m02 - m.m02;
		result.m03 = m03 - m.m03;

		result.m10 = m10 - m.m10;
		result.m11 = m11 - m.m11;
		result.m12 = m12 - m.m12;
		result.m13 = m13 - m.m13;

		result.m20 = m20 - m.m20;
		result.m21 = m21 - m.m21;
		result.m22 = m22 - m.m22;
		result.m23 = m23 - m.m23;

		result.m30 = m30 - m.m30;
		result.m31 = m31 - m.m31;
		result.m32 = m32 - m.m32;
		result.m33 = m33 - m.m33;

		return result;
	}
	Standard_Matrix& operator -= (const Standard_Matrix& m) noexcept { return *this = *this - m; }

	/*
		Scalar Subtraction
	*/
	Standard_Matrix operator - (float s) const noexcept
	{
		Standard_Matrix result;

		result.m00 = m00 - s;
		result.m01 = m01 - s;
		result.m02 = m02 - s;
		result.m03 = m03 - s;

		result.m10 = m10 - s;
		result.m11 = m11 - s;
		result.m12 = m12 - s;
		result.m13 = m13 - s;

		result.m20 = m20 - s;
		result.m21 = m21 - s;
		result.m22 = m22 - s;
		result.m23 = m23 - s;

		result.m30 = m30 - s;
		result.m31 = m31 - s;
		result.m32 = m32 - s;
		result.m33 = m33 - s;

		return result;
	}
	Standard_Matrix& operator -= (float s) noexcept { return *this = *this - s; }

	/*
		Multiplication
	*/
	Standard_Matrix operator * (const Standard_Matrix& m) const
	{
		Standard_Matrix result;

		result.m00 = m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30;
		result.m01 = m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31;
		result.m02 = m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32;
		result.m03 = m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33;

		result.m10 = m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30;
		result.m11 = m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
		result.m12 = m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
		result.m13 = m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33;

		result.m20 = m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30;
		result.m21 = m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
		result.m22 = m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
		result.m23 = m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33;

		result.m30 = m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30;
		result.m31 = m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
		result.m32 = m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
		result.m33 = m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33;

		return result;
	}
	Standard_Matrix& operator *= (const Standard_Matrix& m) noexcept { return *this = *this * m; }

	/*
		Scalar Multiplication
	*/
	Standard_Matrix operator * (float s) const noexcept
	{
		Standard_Matrix result;

		result.m00 = m00 * s;
		result.m01 = m01 * s;
		result.m02 = m02 * s;
		result.m03 = m03 * s;

		result.m10 = m10 * s;
		result.m11 = m11 * s;
		result.m12 = m12 * s;
		result.m13 = m13 * s;

		result.m20 = m20 * s;
		result.m21 = m21 * s;
		result.m22 = m22 * s;
		result.m23 = m23 * s;

		result.m30 = m30 * s;
		result.m31 = m31 * s;
		result.m32 = m32 * s;
		result.m33 = m33 * s;

		return result;
	}
	Standard_Matrix& operator *= (float s) noexcept { return *this = *this * s; }

	/*
		Division
	*/
	Standard_Matrix operator / (const Standard_Matrix& m) const noexcept
	{
		Standard_Matrix result;

		result.m00 = m00 / m.m00;
		result.m01 = m01 / m.m01;
		result.m02 = m02 / m.m02;
		result.m03 = m03 / m.m03;

		result.m10 = m10 / m.m10;
		result.m11 = m11 / m.m11;
		result.m12 = m12 / m.m12;
		result.m13 = m13 / m.m13;

		result.m20 = m20 / m.m20;
		result.m21 = m21 / m.m21;
		result.m22 = m22 / m.m22;
		result.m23 = m23 / m.m23;

		result.m30 = m30 / m.m30;
		result.m31 = m31 / m.m31;
		result.m32 = m32 / m.m32;
		result.m33 = m33 / m.m33;

		return result;
	}
	Standard_Matrix& operator /= (const Standard_Matrix& m) noexcept { return *this = *this / m; }

	/*
		Scalar Division
	*/
	Standard_Matrix operator / (float s) const noexcept
	{
		Standard_Matrix result;

		result.m00 = m00 / s;
		result.m01 = m01 / s;
		result.m02 = m02 / s;
		result.m03 = m03 / s;

		result.m10 = m10 / s;
		result.m11 = m11 / s;
		result.m12 = m12 / s;
		result.m13 = m13 / s;

		result.m20 = m20 / s;
		result.m21 = m21 / s;
		result.m22 = m22 / s;
		result.m23 = m23 / s;

		result.m30 = m30 / s;
		result.m31 = m31 / s;
		result.m32 = m32 / s;
		result.m33 = m33 / s;

		return result;
	}
	Standard_Matrix& operator /= (float s) noexcept { return *this = *this / s; }

	/*
		Data
	*/
	float* data(void) const noexcept { return (float*)this; }

	/*
		Get Vertex
	*/
	Standard_Vertex GetVertex(void) const noexcept { return Standard_Vertex(m03, m13, m23, m33); }

	/*
		Is identity matrix?
	*/
	bool IsIdentity(void) const noexcept;

	/*
		Identity
	*/
	void Identity(void) noexcept;

	/*
		Translate
	*/
	void Translate(float X, float Y, float Z) noexcept;

	/*
		Translate
	*/
	void Translate(Standard_Vertex Vertex) noexcept;

	/*
		Scale
	*/
	void Scale(float S) noexcept;

	/*
		Scale
	*/
	void Scale(float X, float Y, float Z) noexcept;

	/*
		Scale
	*/
	void Scale(Standard_Vertex Vertex) noexcept;

	/*
		Rotate
	*/
	void Rotate(float X, float Y, float Z) noexcept;

	/*
		Rotate
	*/
	void Rotate(Standard_Vertex Vertex) noexcept;

	/*
		Rotate X
	*/
	void RotateX(float Angle) noexcept;

	/*
		Rotate Y
	*/
	void RotateY(float Angle) noexcept;

	/*
		Rotate Z
	*/
	void RotateZ(float Angle) noexcept;

	/*
		Pitch
	*/
	void Pitch(float Angle) noexcept;

	/*
		Yaw
	*/
	void Yaw(float Angle) noexcept;

	/*
		Roll
	*/
	void Roll(float Angle) noexcept;

	/*
		Pitch, Yaw and Roll
	*/
	void PitchYawRoll(float Pitch, float Yaw, float Roll) noexcept;

	/*
		Shear
	*/
	void Shear(float X, float Y, float Z) noexcept;

	/*
		Shear
	*/
	void Shear(Standard_Vertex Vertex) noexcept;

	/*
		Reflect
	*/
	void Reflect(float X, float Y, float Z) noexcept;

	/*
		Reflect
	*/
	void Reflect(Standard_Vertex Vertex) noexcept;

	/*
		Determinant
	*/
	float Determinant(void) const noexcept;

	/*
		Inverse
	*/
	Standard_Matrix Inverse(void) const;

	/*
		Transpose
	*/
	Standard_Matrix Transpose(Standard_Matrix m0, Standard_Matrix m1) const noexcept;

	/*
		Product
	*/
	Standard_Matrix Product(Standard_Matrix m0, Standard_Matrix m1) const noexcept;

	/*
		Orthogonal Left
	*/
	void OrthogonalLeft(float Width, float Height, float zNear, float zFar) noexcept;

	/*
		Orthogonal Right
	*/
	void OrthogonalRight(float Width, float Height, float zNear, float zFar) noexcept;

	/*
		Orthogonal Off-Center Left
	*/
	void OrthogonalOffCenterLeft(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept;

	/*
		Orthogonal Off-Center Right
	*/
	void OrthogonalOffCenterRight(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept;

	/*
		Perspective Left
	*/
	void PerspectiveLeft(float Width, float Height, float zNear, float zFar) noexcept;

	/*
		Perspective Right
	*/
	void PerspectiveRight(float Width, float Height, float zNear, float zFar) noexcept;

	/*
		Perspective FOV Left
	*/
	void PerspectiveFovLeft(float FOV, float Aspect, float zNear, float zFar) noexcept;

	/*
		Perspective FOV Right
	*/
	void PerspectiveFovRight(float FOV, float Aspect, float zNear, float zFar) noexcept;

	/*
		Perspective Off-Center Left
	*/
	void PerspectiveOffCenterLeft(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept;

	/*
		Perspective Off-Center Right
	*/
	void PerspectiveOffCenterRight(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept;

	/*
		LookAt Left
	*/
	void LookAtLeft(const Standard_Vertex& Eye, const Standard_Vertex& At, const Standard_Vertex& Up) noexcept;

	/*
		LookAt Right
	*/
	void LookAtRight(const Standard_Vertex& Eye, const Standard_Vertex& At, const Standard_Vertex& Up) noexcept;

};