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

#include "vertex.h"


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
	explicit Standard_Matrix(vec3 tVertex) noexcept :
		m00(1.0f), m10(0.0f), m20(0.0f), m30(0.0f),
		m01(0.0f), m11(1.0f), m21(0.0f), m31(0.0f),
		m02(0.0f), m12(0.0f), m22(1.0f), m32(0.0f),
		m03(tVertex.x), m13(tVertex.y), m23(tVertex.z), m33(1.0f) {}
	explicit Standard_Matrix(vec3 Translation, vec3 Rotation, vec3 Scale) noexcept
	{
		Standard_Matrix Matrix;
		Matrix.Scale(Scale);
		Matrix.Rotate(Rotation);
		Matrix.Translate(Translation);
		*this = Matrix;
	}

	/*
		Deconstruction
	*/
	~Standard_Matrix() noexcept = default;

	/*
		Copy
	*/
	Standard_Matrix(const Standard_Matrix& m) noexcept :
		m00(m.m00), m10(m.m10), m20(m.m20), m30(m.m30),
		m01(m.m01), m11(m.m11), m21(m.m21), m31(m.m31),
		m02(m.m02), m12(m.m12), m22(m.m22), m32(m.m32),
		m03(m.m03), m13(m.m13), m23(m.m23), m33(m.m33) {}
	Standard_Matrix& operator = (const Standard_Matrix& m) noexcept
	{
		if (this != &m)
		{
			m00 = m.m00; m10 = m.m10; m20 = m.m20; m30 = m.m30;
			m01 = m.m01; m11 = m.m11; m21 = m.m21; m31 = m.m31;
			m02 = m.m02; m12 = m.m12; m22 = m.m22; m32 = m.m32;
			m03 = m.m03; m13 = m.m13; m23 = m.m23; m33 = m.m33;
		}
		return *this;
	}

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
		if (this != &m)
		{
			m00 = std::exchange(m.m00, 0.0f); m10 = std::exchange(m.m10, 0.0f); m20 = std::exchange(m.m20, 0.0f); m30 = std::exchange(m.m30, 0.0f);
			m01 = std::exchange(m.m01, 0.0f); m11 = std::exchange(m.m11, 0.0f); m21 = std::exchange(m.m21, 0.0f); m31 = std::exchange(m.m31, 0.0f);
			m02 = std::exchange(m.m02, 0.0f); m12 = std::exchange(m.m12, 0.0f); m22 = std::exchange(m.m22, 0.0f); m32 = std::exchange(m.m32, 0.0f);
			m03 = std::exchange(m.m03, 0.0f); m13 = std::exchange(m.m13, 0.0f); m23 = std::exchange(m.m23, 0.0f); m33 = std::exchange(m.m33, 0.0f);
		}
		return *this;
	}

	/*
		Unary
	*/
	Standard_Matrix operator - (void) const noexcept
	{
		Standard_Matrix Matrix;

		Matrix.m00 = -m00;
		Matrix.m01 = -m01;
		Matrix.m02 = -m02;
		Matrix.m03 = -m03;

		Matrix.m10 = -m10;
		Matrix.m11 = -m11;
		Matrix.m12 = -m12;
		Matrix.m13 = -m13;

		Matrix.m20 = -m20;
		Matrix.m21 = -m21;
		Matrix.m22 = -m22;
		Matrix.m23 = -m23;

		Matrix.m30 = -m30;
		Matrix.m31 = -m31;
		Matrix.m32 = -m32;
		Matrix.m33 = -m33;

		return Matrix;
	}

	/*
		Equality
	*/
	bool operator == (const Standard_Matrix& m) const noexcept
	{
		return
			m00 == m.m00 && m10 == m.m10 && m20 == m.m20 && m30 == m.m30 &&
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
		Standard_Matrix Matrix;

		Matrix.m00 = m00 + m.m00;
		Matrix.m01 = m01 + m.m01;
		Matrix.m02 = m02 + m.m02;
		Matrix.m03 = m03 + m.m03;

		Matrix.m10 = m10 + m.m10;
		Matrix.m11 = m11 + m.m11;
		Matrix.m12 = m12 + m.m12;
		Matrix.m13 = m13 + m.m13;

		Matrix.m20 = m20 + m.m20;
		Matrix.m21 = m21 + m.m21;
		Matrix.m22 = m22 + m.m22;
		Matrix.m23 = m23 + m.m23;

		Matrix.m30 = m30 + m.m30;
		Matrix.m31 = m31 + m.m31;
		Matrix.m32 = m32 + m.m32;
		Matrix.m33 = m33 + m.m33;

		return Matrix;
	}
	Standard_Matrix& operator += (const Standard_Matrix& m) noexcept { return *this = *this + m; }

	/*
		Scalar Addition
	*/
	Standard_Matrix operator + (float s) const noexcept
	{
		Standard_Matrix Matrix;

		Matrix.m00 = m00 + s;
		Matrix.m01 = m01 + s;
		Matrix.m02 = m02 + s;
		Matrix.m03 = m03 + s;

		Matrix.m10 = m10 + s;
		Matrix.m11 = m11 + s;
		Matrix.m12 = m12 + s;
		Matrix.m13 = m13 + s;

		Matrix.m20 = m20 + s;
		Matrix.m21 = m21 + s;
		Matrix.m22 = m22 + s;
		Matrix.m23 = m23 + s;

		Matrix.m30 = m30 + s;
		Matrix.m31 = m31 + s;
		Matrix.m32 = m32 + s;
		Matrix.m33 = m33 + s;

		return Matrix;
	}
	Standard_Matrix& operator += (float s) noexcept { return *this = *this + s; }

	/*
		Subtraction
	*/
	Standard_Matrix operator - (const Standard_Matrix& m) const noexcept
	{
		Standard_Matrix Matrix;

		Matrix.m00 = m00 - m.m00;
		Matrix.m01 = m01 - m.m01;
		Matrix.m02 = m02 - m.m02;
		Matrix.m03 = m03 - m.m03;

		Matrix.m10 = m10 - m.m10;
		Matrix.m11 = m11 - m.m11;
		Matrix.m12 = m12 - m.m12;
		Matrix.m13 = m13 - m.m13;

		Matrix.m20 = m20 - m.m20;
		Matrix.m21 = m21 - m.m21;
		Matrix.m22 = m22 - m.m22;
		Matrix.m23 = m23 - m.m23;

		Matrix.m30 = m30 - m.m30;
		Matrix.m31 = m31 - m.m31;
		Matrix.m32 = m32 - m.m32;
		Matrix.m33 = m33 - m.m33;

		return Matrix;
	}
	Standard_Matrix& operator -= (const Standard_Matrix& m) noexcept { return *this = *this - m; }

	/*
		Scalar Subtraction
	*/
	Standard_Matrix operator - (float s) const noexcept
	{
		Standard_Matrix Matrix;

		Matrix.m00 = m00 - s;
		Matrix.m01 = m01 - s;
		Matrix.m02 = m02 - s;
		Matrix.m03 = m03 - s;

		Matrix.m10 = m10 - s;
		Matrix.m11 = m11 - s;
		Matrix.m12 = m12 - s;
		Matrix.m13 = m13 - s;

		Matrix.m20 = m20 - s;
		Matrix.m21 = m21 - s;
		Matrix.m22 = m22 - s;
		Matrix.m23 = m23 - s;

		Matrix.m30 = m30 - s;
		Matrix.m31 = m31 - s;
		Matrix.m32 = m32 - s;
		Matrix.m33 = m33 - s;

		return Matrix;
	}
	Standard_Matrix& operator -= (float s) noexcept { return *this = *this - s; }

	/*
		Multiplication
	*/
	Standard_Matrix operator * (const Standard_Matrix& m) const
	{
		Standard_Matrix Matrix;

		Matrix.m00 = m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30;
		Matrix.m01 = m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31;
		Matrix.m02 = m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32;
		Matrix.m03 = m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33;

		Matrix.m10 = m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30;
		Matrix.m11 = m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
		Matrix.m12 = m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
		Matrix.m13 = m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33;

		Matrix.m20 = m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30;
		Matrix.m21 = m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
		Matrix.m22 = m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
		Matrix.m23 = m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33;

		Matrix.m30 = m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30;
		Matrix.m31 = m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
		Matrix.m32 = m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
		Matrix.m33 = m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33;

		return Matrix;
	}
	Standard_Matrix& operator *= (const Standard_Matrix& m) noexcept { return *this = *this * m; }

	/*
		Scalar Multiplication
	*/
	Standard_Matrix operator * (float s) const noexcept
	{
		Standard_Matrix Matrix;

		Matrix.m00 = m00 * s;
		Matrix.m01 = m01 * s;
		Matrix.m02 = m02 * s;
		Matrix.m03 = m03 * s;

		Matrix.m10 = m10 * s;
		Matrix.m11 = m11 * s;
		Matrix.m12 = m12 * s;
		Matrix.m13 = m13 * s;

		Matrix.m20 = m20 * s;
		Matrix.m21 = m21 * s;
		Matrix.m22 = m22 * s;
		Matrix.m23 = m23 * s;

		Matrix.m30 = m30 * s;
		Matrix.m31 = m31 * s;
		Matrix.m32 = m32 * s;
		Matrix.m33 = m33 * s;

		return Matrix;
	}
	Standard_Matrix& operator *= (float s) noexcept { return *this = *this * s; }

	/*
		Division
	*/
	Standard_Matrix operator / (const Standard_Matrix& m) const noexcept
	{
		Standard_Matrix Matrix;

		Matrix.m00 = m00 / m.m00;
		Matrix.m01 = m01 / m.m01;
		Matrix.m02 = m02 / m.m02;
		Matrix.m03 = m03 / m.m03;

		Matrix.m10 = m10 / m.m10;
		Matrix.m11 = m11 / m.m11;
		Matrix.m12 = m12 / m.m12;
		Matrix.m13 = m13 / m.m13;

		Matrix.m20 = m20 / m.m20;
		Matrix.m21 = m21 / m.m21;
		Matrix.m22 = m22 / m.m22;
		Matrix.m23 = m23 / m.m23;

		Matrix.m30 = m30 / m.m30;
		Matrix.m31 = m31 / m.m31;
		Matrix.m32 = m32 / m.m32;
		Matrix.m33 = m33 / m.m33;

		return Matrix;
	}
	Standard_Matrix& operator /= (const Standard_Matrix& m) noexcept { return *this = *this / m; }

	/*
		Scalar Division
	*/
	Standard_Matrix operator / (float s) const noexcept
	{
		Standard_Matrix Matrix;

		Matrix.m00 = m00 / s;
		Matrix.m01 = m01 / s;
		Matrix.m02 = m02 / s;
		Matrix.m03 = m03 / s;

		Matrix.m10 = m10 / s;
		Matrix.m11 = m11 / s;
		Matrix.m12 = m12 / s;
		Matrix.m13 = m13 / s;

		Matrix.m20 = m20 / s;
		Matrix.m21 = m21 / s;
		Matrix.m22 = m22 / s;
		Matrix.m23 = m23 / s;

		Matrix.m30 = m30 / s;
		Matrix.m31 = m31 / s;
		Matrix.m32 = m32 / s;
		Matrix.m33 = m33 / s;

		return Matrix;
	}
	Standard_Matrix& operator /= (float s) noexcept { return *this = *this / s; }

	/*
		Data
	*/
	float* data(void) const noexcept { return (float*)this; }

	/*
		Get Vector
	*/
	vec3 GetVector(void) const noexcept { return vec3(m03, m13, m23); }

	/*
		Is identity matrix?
	*/
	bool IsIdentity(void) const noexcept
	{
		return
			m00 == 1.0f && m10 == 0.0f && m20 == 0.0f && m30 == 0.0f &&
			m01 == 0.0f && m11 == 1.0f && m21 == 0.0f && m31 == 0.0f &&
			m02 == 0.0f && m12 == 0.0f && m22 == 1.0f && m32 == 0.0f &&
			m03 == 0.0f && m13 == 0.0f && m23 == 0.0f && m33 == 1.0f;
	}

	/*
		Identity
	*/
	void Identity(void) noexcept
	{
		m00 = 1.0f; m10 = 0.0f; m20 = 0.0f; m30 = 0.0f;
		m01 = 0.0f; m11 = 1.0f; m21 = 0.0f; m31 = 0.0f;
		m02 = 0.0f; m12 = 0.0f; m22 = 1.0f; m32 = 0.0f;
		m03 = 0.0f; m13 = 0.0f; m23 = 0.0f; m33 = 1.0f;
	}

	/*
		Translate
	*/
	Standard_Matrix Translate(float X, float Y, float Z) noexcept { return Translate(vec3{ X, Y, Z }); }

	/*
		Translate
	*/
	Standard_Matrix Translate(vec3 Vector) noexcept;

	/*
		Scale
	*/
	Standard_Matrix Scale(float S) noexcept { return Scale(vec3{ S, S, S }); }

	/*
		Scale
	*/
	Standard_Matrix Scale(float X, float Y, float Z) noexcept { return Scale(vec3{ X, Y, Z }); }

	/*
		Scale
	*/
	Standard_Matrix Scale(vec3 Vector) noexcept;

	/*
		Rotate
	*/
	Standard_Matrix Rotate(float X, float Y, float Z) noexcept { return Rotate(vec3{ X, Y, Z }); }

	/*
		Rotate
	*/
	Standard_Matrix Rotate(vec3 Vector) noexcept;

	/*
		Rotate X
	*/
	Standard_Matrix RotateX(float Angle) noexcept;

	/*
		Rotate Y
	*/
	Standard_Matrix RotateY(float Angle) noexcept;

	/*
		Rotate Z
	*/
	Standard_Matrix RotateZ(float Angle) noexcept;

	/*
		Pitch, Yaw and Roll
	*/
	Standard_Matrix PitchYawRoll(float Pitch, float Yaw, float Roll) noexcept { return PitchYawRoll(vec3{ Pitch, Yaw, Roll }); }

	/*
		Pitch, Yaw and Roll
	*/
	Standard_Matrix PitchYawRoll(vec3 Vector) noexcept;

	/*
		Pitch
	*/
	Standard_Matrix Pitch(float Angle) noexcept;

	/*
		Yaw
	*/
	Standard_Matrix Yaw(float Angle) noexcept;

	/*
		Roll
	*/
	Standard_Matrix Roll(float Angle) noexcept;

	/*
		Shear
	*/
	Standard_Matrix Shear(float X, float Y, float Z) noexcept { return Shear(vec3{ X, Y, Z }); }

	/*
		Shear
	*/
	Standard_Matrix Shear(vec3 Vector) noexcept;

	/*
		Reflect
	*/
	Standard_Matrix Reflect(float X, float Y, float Z) noexcept { return Reflect(vec3{ X, Y, Z }); }

	/*
		Reflect
	*/
	Standard_Matrix Reflect(vec3 Vector) noexcept;

	/*
		Determinant
	*/
	float Determinant(void) const noexcept
	{
		return
			m00 * m11 * m22 * m33 + m00 * m12 * m23 * m31 + m00 * m13 * m21 * m32 +
			m01 * m10 * m23 * m32 + m01 * m12 * m20 * m33 + m01 * m13 * m22 * m30 +
			m02 * m10 * m21 * m33 + m02 * m11 * m23 * m30 + m02 * m13 * m20 * m31 +
			m03 * m10 * m22 * m31 + m03 * m11 * m20 * m32 + m03 * m12 * m21 * m30 -
			m00 * m11 * m23 * m32 - m00 * m12 * m21 * m33 - m00 * m13 * m22 * m31 -
			m01 * m10 * m22 * m33 - m01 * m12 * m23 * m30 - m01 * m13 * m20 * m32 -
			m02 * m10 * m23 * m31 - m02 * m11 * m20 * m33 - m02 * m13 * m21 * m30 -
			m03 * m10 * m21 * m32 - m03 * m11 * m22 * m30 - m03 * m12 * m20 * m31;
	}

	/*
		Inverse
	*/
	Standard_Matrix Inverse(void) const;

	/*
		Transpose
	*/
	Standard_Matrix Transpose(Standard_Matrix m0, Standard_Matrix m1) const noexcept;

	/*
		Dot
	*/
	Standard_Matrix Dot(Standard_Matrix& m0, Standard_Matrix& m1) const noexcept;

	/*
		Product
	*/
	Standard_Matrix Product(Standard_Matrix m0, Standard_Matrix m1) const noexcept;

	/*
		Set World Matrix
	*/
	Standard_Matrix SetWorld(const vec3& mTranslation, const vec3& mRotation, const vec3& mScale) noexcept;

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
	void LookAtLeft(const vec3& Eye, const vec3& At, const vec3& Up) noexcept;

	/*
		LookAt Right
	*/
	void LookAtRight(const vec3& Eye, const vec3& At, const vec3& Up) noexcept;

};