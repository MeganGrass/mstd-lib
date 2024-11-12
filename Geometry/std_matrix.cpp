/*
*
*	Megan Grass
*	April 11, 2024
*
*
*	TODO:
*
*/


#include "std_matrix.h"


/*
	Is identity matrix?
*/
bool Standard_Matrix::IsIdentity(void) const noexcept
{
	return m00 == 1.0f && m10 == 0.0f && m20 == 0.0f && m30 == 0.0f &&
		m01 == 0.0f && m11 == 1.0f && m21 == 0.0f && m31 == 0.0f &&
		m02 == 0.0f && m12 == 0.0f && m22 == 1.0f && m32 == 0.0f &&
		m03 == 0.0f && m13 == 0.0f && m23 == 0.0f && m33 == 1.0f;
}


/*
	Identity
*/
void Standard_Matrix::Identity(void) noexcept
{
	m00 = 1.0f; m10 = 0.0f; m20 = 0.0f; m30 = 0.0f;
	m01 = 0.0f; m11 = 1.0f; m21 = 0.0f; m31 = 0.0f;
	m02 = 0.0f; m12 = 0.0f; m22 = 1.0f; m32 = 0.0f;
	m03 = 0.0f; m13 = 0.0f; m23 = 0.0f; m33 = 1.0f;
}


/*
	Translate
*/
void Standard_Matrix::Translate(float X, float Y, float Z) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m03 = X;
	Matrix.m13 = Y;
	Matrix.m23 = Z;
	*this *= Matrix;
}


/*
	Translate
*/
void Standard_Matrix::Translate(Standard_Vertex Vertex) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m03 = Vertex.x;
	Matrix.m13 = Vertex.y;
	Matrix.m23 = Vertex.z;
	*this *= Matrix;
}


/*
	Scale
*/
void Standard_Matrix::Scale(float S) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = S;
	Matrix.m11 = S;
	Matrix.m22 = S;
	*this *= Matrix;
}


/*
	Scale
*/
void Standard_Matrix::Scale(float X, float Y, float Z) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = X;
	Matrix.m11 = Y;
	Matrix.m22 = Z;
	*this *= Matrix;
}


/*
	Scale
*/
void Standard_Matrix::Scale(Standard_Vertex Vertex) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = Vertex.x;
	Matrix.m11 = Vertex.y;
	Matrix.m22 = Vertex.z;
	*this *= Matrix;
}


/*
	Rotate
*/
void Standard_Matrix::Rotate(float X, float Y, float Z) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Y) * cosf(Z);
	Matrix.m01 = cosf(Y) * sinf(Z);
	Matrix.m02 = -sinf(Y);
	Matrix.m10 = sinf(X) * sinf(Y) * cosf(Z) - cosf(X) * sinf(Z);
	Matrix.m11 = sinf(X) * sinf(Y) * sinf(Z) + cosf(X) * cosf(Z);
	Matrix.m12 = sinf(X) * cosf(Y);
	Matrix.m20 = cosf(X) * sinf(Y) * cosf(Z) + sinf(X) * sinf(Z);
	Matrix.m21 = cosf(X) * sinf(Y) * sinf(Z) - sinf(X) * cosf(Z);
	Matrix.m22 = cosf(X) * cosf(Y);
	*this *= Matrix;
}


/*
	Rotate
*/
void Standard_Matrix::Rotate(Standard_Vertex Vertex) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Vertex.y) * cosf(Vertex.z);
	Matrix.m01 = cosf(Vertex.y) * sinf(Vertex.z);
	Matrix.m02 = -sinf(Vertex.y);
	Matrix.m10 = sinf(Vertex.x) * sinf(Vertex.y) * cosf(Vertex.z) - cosf(Vertex.x) * sinf(Vertex.z);
	Matrix.m11 = sinf(Vertex.x) * sinf(Vertex.y) * sinf(Vertex.z) + cosf(Vertex.x) * cosf(Vertex.z);
	Matrix.m12 = sinf(Vertex.x) * cosf(Vertex.y);
	Matrix.m20 = cosf(Vertex.x) * sinf(Vertex.y) * cosf(Vertex.z) + sinf(Vertex.x) * sinf(Vertex.z);
	Matrix.m21 = cosf(Vertex.x) * sinf(Vertex.y) * sinf(Vertex.z) - sinf(Vertex.x) * cosf(Vertex.z);
	Matrix.m22 = cosf(Vertex.x) * cosf(Vertex.y);
	*this *= Matrix;
}


/*
	Rotate X
*/
void Standard_Matrix::RotateX(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m11 = cosf(Angle);
	Matrix.m12 = sinf(Angle);
	Matrix.m21 = -sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this *= Matrix;
}


/*
	Rotate Y
*/
void Standard_Matrix::RotateY(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m02 = -sinf(Angle);
	Matrix.m20 = sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this *= Matrix;
}


/*
	Rotate Z
*/
void Standard_Matrix::RotateZ(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m01 = sinf(Angle);
	Matrix.m10 = -sinf(Angle);
	Matrix.m11 = cosf(Angle);
	*this *= Matrix;
}


/*
	Pitch
*/
void Standard_Matrix::Pitch(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m11 = cosf(Angle);
	Matrix.m12 = sinf(Angle);
	Matrix.m21 = -sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this = Transpose(Matrix, *this);
}


/*
	Yaw
*/
void Standard_Matrix::Yaw(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m02 = -sinf(Angle);
	Matrix.m20 = sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this = Transpose(Matrix, *this);
}


/*
	Roll
*/
void Standard_Matrix::Roll(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m01 = sinf(Angle);
	Matrix.m10 = -sinf(Angle);
	Matrix.m11 = cosf(Angle);
	*this = Transpose(Matrix, *this);
}


/*
	Pitch, Yaw and Roll
*/
void Standard_Matrix::PitchYawRoll(float Pitch, float Yaw, float Roll) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Yaw) * cosf(Roll);
	Matrix.m01 = cosf(Yaw) * sinf(Roll);
	Matrix.m02 = -sinf(Yaw);
	Matrix.m10 = sinf(Pitch) * sinf(Yaw) * cosf(Roll) - cosf(Pitch) * sinf(Roll);
	Matrix.m11 = sinf(Pitch) * sinf(Yaw) * sinf(Roll) + cosf(Pitch) * cosf(Roll);
	Matrix.m12 = sinf(Pitch) * cosf(Yaw);
	Matrix.m20 = cosf(Pitch) * sinf(Yaw) * cosf(Roll) + sinf(Pitch) * sinf(Roll);
	Matrix.m21 = cosf(Pitch) * sinf(Yaw) * sinf(Roll) - sinf(Pitch) * cosf(Roll);
	Matrix.m22 = cosf(Pitch) * cosf(Yaw);
	*this = Transpose(Matrix, *this);
}


/*
	Shear
*/
void Standard_Matrix::Shear(float X, float Y, float Z) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m01 = X;
	Matrix.m02 = Y;
	Matrix.m10 = Z;
	Matrix.m12 = X;
	Matrix.m20 = Y;
	Matrix.m21 = Z;
	*this *= Matrix;
}


/*
	Shear
*/
void Standard_Matrix::Shear(Standard_Vertex Vertex) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m01 = Vertex.x;
	Matrix.m02 = Vertex.y;
	Matrix.m10 = Vertex.z;
	Matrix.m12 = Vertex.x;
	Matrix.m20 = Vertex.y;
	Matrix.m21 = Vertex.z;
	*this *= Matrix;
}


/*
	Reflect
*/
void Standard_Matrix::Reflect(float X, float Y, float Z) noexcept
{
	Standard_Vertex Vertex(X, Y, Z);
	Reflect(Vertex);
}


/*
	Reflect
*/
void Standard_Matrix::Reflect(Standard_Vertex Vertex) noexcept
{
	Vertex = Vertex.Normalize();
	Standard_Matrix Matrix;
	Matrix.m00 = 1.0f - 2.0f * Vertex.x * Vertex.x;
	Matrix.m11 = 1.0f - 2.0f * Vertex.y * Vertex.y;
	Matrix.m22 = 1.0f - 2.0f * Vertex.z * Vertex.z;
	Matrix.m01 = -2.0f * Vertex.x * Vertex.y;
	Matrix.m02 = -2.0f * Vertex.x * Vertex.z;
	Matrix.m10 = -2.0f * Vertex.y * Vertex.x;
	Matrix.m12 = -2.0f * Vertex.y * Vertex.z;
	Matrix.m20 = -2.0f * Vertex.z * Vertex.x;
	Matrix.m21 = -2.0f * Vertex.z * Vertex.y;
	*this *= Matrix;
}


/*
	Determinant
*/
float Standard_Matrix::Determinant(void) const noexcept
{
	return m00 * m11 * m22 * m33 + m00 * m12 * m23 * m31 + m00 * m13 * m21 * m32 +
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
Standard_Matrix Standard_Matrix::Inverse(void) const
{
	Standard_Matrix Matrix;

	float det = Determinant();
	if (det == 0.0f)
	{
		std::cout << "Cannot invert a matrix with a determinant of 0" << std::endl;
		return Matrix;
	}

	float invDet = 1.0f / det;

	Matrix.m00 = invDet * (m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31);
	Matrix.m01 = -invDet * (m01 * m22 * m33 + m02 * m23 * m31 + m03 * m21 * m32 - m01 * m23 * m32 - m02 * m21 * m33 - m03 * m22 * m31);
	Matrix.m02 = invDet * (m01 * m12 * m33 + m02 * m13 * m31 + m03 * m11 * m32 - m01 * m13 * m32 - m02 * m11 * m33 - m03 * m12 * m31);
	Matrix.m03 = -invDet * (m01 * m12 * m23 + m02 * m13 * m21 + m03 * m11 * m22 - m01 * m13 * m22 - m02 * m11 * m23 - m03 * m12 * m21);

	Matrix.m10 = -invDet * (m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32 - m10 * m23 * m32 - m12 * m20 * m33 - m13 * m22 * m30);
	Matrix.m11 = invDet * (m00 * m22 * m33 + m02 * m23 * m30 + m03 * m20 * m32 - m00 * m23 * m32 - m02 * m20 * m33 - m03 * m22 * m30);
	Matrix.m12 = -invDet * (m00 * m12 * m33 + m02 * m13 * m30 + m03 * m10 * m32 - m00 * m13 * m32 - m02 * m10 * m33 - m03 * m12 * m30);
	Matrix.m13 = invDet * (m00 * m12 * m23 + m02 * m13 * m20 + m03 * m10 * m22 - m00 * m13 * m22 - m02 * m10 * m23 - m03 * m12 * m20);

	Matrix.m20 = invDet * (m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31 - m10 * m23 * m31 - m11 * m20 * m33 - m13 * m21 * m30);
	Matrix.m21 = -invDet * (m00 * m21 * m33 + m01 * m23 * m30 + m03 * m20 * m31 - m00 * m23 * m31 - m01 * m20 * m33 - m03 * m21 * m30);
	Matrix.m22 = invDet * (m00 * m11 * m33 + m01 * m13 * m30 + m03 * m10 * m31 - m00 * m13 * m31 - m01 * m10 * m33 - m03 * m11 * m30);
	Matrix.m23 = -invDet * (m00 * m11 * m23 + m01 * m13 * m20 + m03 * m10 * m21 - m00 * m13 * m21 - m01 * m10 * m23 - m03 * m11 * m20);

	Matrix.m30 = -invDet * (m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31 - m10 * m22 * m31 - m11 * m20 * m32 - m12 * m21 * m30);
	Matrix.m31 = invDet * (m00 * m21 * m32 + m01 * m22 * m30 + m02 * m20 * m31 - m00 * m22 * m31 - m01 * m20 * m32 - m02 * m21 * m30);
	Matrix.m32 = -invDet * (m00 * m11 * m32 + m01 * m12 * m30 + m02 * m10 * m31 - m00 * m12 * m31 - m01 * m10 * m32 - m02 * m11 * m30);
	Matrix.m33 = invDet * (m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m00 * m12 * m21 - m01 * m10 * m22 - m02 * m11 * m20);

	return Matrix;
}


/*
	Transpose
*/
Standard_Matrix Standard_Matrix::Transpose(Standard_Matrix m0, Standard_Matrix m1) const noexcept
{
	Standard_Matrix Matrix;

	Matrix.m00 = m0.m00 * m1.m00 + m0.m10 * m1.m10 + m0.m20 * m1.m20 + m0.m30 * m1.m30;
	Matrix.m01 = m0.m00 * m1.m01 + m0.m10 * m1.m11 + m0.m20 * m1.m21 + m0.m30 * m1.m31;
	Matrix.m02 = m0.m00 * m1.m02 + m0.m10 * m1.m12 + m0.m20 * m1.m22 + m0.m30 * m1.m32;
	Matrix.m03 = m0.m00 * m1.m03 + m0.m10 * m1.m13 + m0.m20 * m1.m23 + m0.m30 * m1.m33;

	Matrix.m10 = m0.m01 * m1.m00 + m0.m11 * m1.m10 + m0.m21 * m1.m20 + m0.m31 * m1.m30;
	Matrix.m11 = m0.m01 * m1.m01 + m0.m11 * m1.m11 + m0.m21 * m1.m21 + m0.m31 * m1.m31;
	Matrix.m12 = m0.m01 * m1.m02 + m0.m11 * m1.m12 + m0.m21 * m1.m22 + m0.m31 * m1.m32;
	Matrix.m13 = m0.m01 * m1.m03 + m0.m11 * m1.m13 + m0.m21 * m1.m23 + m0.m31 * m1.m33;

	Matrix.m20 = m0.m02 * m1.m00 + m0.m12 * m1.m10 + m0.m22 * m1.m20 + m0.m32 * m1.m30;
	Matrix.m21 = m0.m02 * m1.m01 + m0.m12 * m1.m11 + m0.m22 * m1.m21 + m0.m32 * m1.m31;
	Matrix.m22 = m0.m02 * m1.m02 + m0.m12 * m1.m12 + m0.m22 * m1.m22 + m0.m32 * m1.m32;
	Matrix.m23 = m0.m02 * m1.m03 + m0.m12 * m1.m13 + m0.m22 * m1.m23 + m0.m32 * m1.m33;

	Matrix.m30 = m0.m03 * m1.m00 + m0.m13 * m1.m10 + m0.m23 * m1.m20 + m0.m33 * m1.m30;
	Matrix.m31 = m0.m03 * m1.m01 + m0.m13 * m1.m11 + m0.m23 * m1.m21 + m0.m33 * m1.m31;
	Matrix.m32 = m0.m03 * m1.m02 + m0.m13 * m1.m12 + m0.m23 * m1.m22 + m0.m33 * m1.m32;
	Matrix.m33 = m0.m03 * m1.m03 + m0.m13 * m1.m13 + m0.m23 * m1.m23 + m0.m33 * m1.m33;

	return Matrix;
}


/*
	Product
*/
Standard_Matrix Standard_Matrix::Product(Standard_Matrix m0, Standard_Matrix m1) const noexcept
{
	Standard_Matrix Matrix;

	Matrix.m00 = m0.m00 * m1.m00 + m0.m10 * m1.m01 + m0.m20 * m1.m02 + m0.m30 * m1.m03;
	Matrix.m01 = m0.m01 * m1.m00 + m0.m11 * m1.m01 + m0.m21 * m1.m02 + m0.m31 * m1.m03;
	Matrix.m02 = m0.m02 * m1.m00 + m0.m12 * m1.m01 + m0.m22 * m1.m02 + m0.m32 * m1.m03;
	Matrix.m03 = m0.m03 * m1.m00 + m0.m13 * m1.m01 + m0.m23 * m1.m02 + m0.m33 * m1.m03;

	Matrix.m10 = m0.m00 * m1.m10 + m0.m10 * m1.m11 + m0.m20 * m1.m12 + m0.m30 * m1.m13;
	Matrix.m11 = m0.m01 * m1.m10 + m0.m11 * m1.m11 + m0.m21 * m1.m12 + m0.m31 * m1.m13;
	Matrix.m12 = m0.m02 * m1.m10 + m0.m12 * m1.m11 + m0.m22 * m1.m12 + m0.m32 * m1.m13;
	Matrix.m13 = m0.m03 * m1.m10 + m0.m13 * m1.m11 + m0.m23 * m1.m12 + m0.m33 * m1.m13;

	Matrix.m20 = m0.m00 * m1.m20 + m0.m10 * m1.m21 + m0.m20 * m1.m22 + m0.m30 * m1.m23;
	Matrix.m21 = m0.m01 * m1.m20 + m0.m11 * m1.m21 + m0.m21 * m1.m22 + m0.m31 * m1.m23;
	Matrix.m22 = m0.m02 * m1.m20 + m0.m12 * m1.m21 + m0.m22 * m1.m22 + m0.m32 * m1.m23;
	Matrix.m23 = m0.m03 * m1.m20 + m0.m13 * m1.m21 + m0.m23 * m1.m22 + m0.m33 * m1.m23;

	Matrix.m30 = m0.m00 * m1.m30 + m0.m10 * m1.m31 + m0.m20 * m1.m32 + m0.m30 * m1.m33;
	Matrix.m31 = m0.m01 * m1.m30 + m0.m11 * m1.m31 + m0.m21 * m1.m32 + m0.m31 * m1.m33;
	Matrix.m32 = m0.m02 * m1.m30 + m0.m12 * m1.m31 + m0.m22 * m1.m32 + m0.m32 * m1.m33;
	Matrix.m33 = m0.m03 * m1.m30 + m0.m13 * m1.m31 + m0.m23 * m1.m32 + m0.m33 * m1.m33;

	return Matrix;
}


/*
	Orthogonal Left
*/
void Standard_Matrix::OrthogonalLeft(float Width, float Height, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f / Width;
	m11 = 2.0f / Height;
	m22 = 1.0f / (zFar - zNear);
	m23 = -zNear / (zFar - zNear);
	m33 = 1.0f;

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Orthogonal Right
*/
void Standard_Matrix::OrthogonalRight(float Width, float Height, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f / Width;
	m11 = 2.0f / Height;
	m22 = 1.0f / (zNear - zFar);
	m23 = zNear / (zNear - zFar);
	m33 = 1.0f;

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Orthogonal Off-Center Left
*/
void Standard_Matrix::OrthogonalOffCenterLeft(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f / (Right - Left);
	m11 = 2.0f / (Top - Bottom);
	m22 = 1.0f / (zFar - zNear);
	m23 = -zNear / (zFar - zNear);
	m33 = 1.0f;

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Orthogonal Off-Center Right
*/
void Standard_Matrix::OrthogonalOffCenterRight(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f / (Right - Left);
	m11 = 2.0f / (Top - Bottom);
	m22 = 1.0f / (zNear - zFar);
	m23 = zNear / (zNear - zFar);
	m33 = 1.0f;

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Perspective Left
*/
void Standard_Matrix::PerspectiveLeft(float Width, float Height, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f * zNear / Width;
	m11 = 2.0f * zNear / Height;
	m22 = zFar / (zFar - zNear);
	m23 = 1.0f;
	m32 = zNear * zFar / (zNear - zFar);

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Perspective Right
*/
void Standard_Matrix::PerspectiveRight(float Width, float Height, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f * zNear / Width;
	m11 = 2.0f * zNear / Height;
	m22 = zFar / (zNear - zFar);
	m23 = -1.0f;
	m32 = zNear * zFar / (zNear - zFar);

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Perspective FOV Left
*/
void Standard_Matrix::PerspectiveFovLeft(float FOV, float Aspect, float zNear, float zFar) noexcept
{
	Identity();
	float yScale = 1.0f / tanf(FOV / 2.0f);
	float xScale = yScale / Aspect;

	m00 = xScale;
	m11 = yScale;
	m22 = zFar / (zNear - zFar);
	m23 = 1.0f;
	m32 = zNear * zFar / (zNear - zFar);
	m33 = 0.0f;

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Perspective FOV Right
*/
void Standard_Matrix::PerspectiveFovRight(float FOV, float Aspect, float zNear, float zFar) noexcept
{
	Identity();
	float yScale = 1.0f / tanf(FOV / 2.0f);
	float xScale = yScale / Aspect;

	m00 = xScale;
	m11 = yScale;
	m22 = zFar / (zNear - zFar);
	m23 = -1.0f;
	m32 = zNear * zFar / (zNear - zFar);
	m33 = 0.0f;

	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = 0.0f;
}


/*
	Perspective Off-Center Left
*/
void Standard_Matrix::PerspectiveOffCenterLeft(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f * zNear / (Right - Left);
	m11 = 2.0f * zNear / (Top - Bottom);
	m20 = (Right + Left) / (Right - Left);
	m21 = (Top + Bottom) / (Top - Bottom);
	m22 = zFar / (zNear - zFar);
	m23 = 1.0f;
	m32 = zNear * zFar / (zNear - zFar);

	m01 = m02 = m03 = m10 = m12 = m13 = m30 = m31 = 0.0f;
}


/*
	Perspective Off-Center Right
*/
void Standard_Matrix::PerspectiveOffCenterRight(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f * zNear / (Right - Left);
	m11 = 2.0f * zNear / (Top - Bottom);
	m20 = (Right + Left) / (Left - Right);
	m21 = (Top + Bottom) / (Bottom - Top);
	m22 = zFar / (zNear - zFar);
	m23 = -1.0f;

	m01 = m02 = m03 = m10 = m12 = m13 = m30 = m31 = 0.0f;
}


/*
	LookAt Left
*/
void Standard_Matrix::LookAtLeft(const Standard_Vertex& Eye, const Standard_Vertex& At, const Standard_Vertex& Up) noexcept
{
	Standard_Vertex Z = (At - Eye).Normalize();
	Standard_Vertex X = Up.Cross(Z).Normalize();
	Standard_Vertex Y = Z.Cross(X);

	m00 = X.x;
	m01 = X.y;
	m02 = X.z;
	m03 = -X.Dot(Eye);

	m10 = Y.x;
	m11 = Y.y;
	m12 = Y.z;
	m13 = -Y.Dot(Eye);

	m20 = Z.x;
	m21 = Z.y;
	m22 = Z.z;
	m23 = -Z.Dot(Eye);

	m30 = 0.0f;
	m31 = 0.0f;
	m32 = 0.0f;
	m33 = 1.0f;
}


/*
	LookAt Right
*/
void Standard_Matrix::LookAtRight(const Standard_Vertex& Eye, const Standard_Vertex& At, const Standard_Vertex& Up) noexcept
{
	Standard_Vertex Z = (Eye - At).Normalize();
	Standard_Vertex X = Up.Cross(Z).Normalize();
	Standard_Vertex Y = Z.Cross(X);

	m00 = X.x;
	m01 = X.y;
	m02 = X.z;
	m03 = -X.Dot(Eye);

	m10 = Y.x;
	m11 = Y.y;
	m12 = Y.z;
	m13 = -Y.Dot(Eye);

	m20 = Z.x;
	m21 = Z.y;
	m22 = Z.z;
	m23 = -Z.Dot(Eye);

	m30 = 0.0f;
	m31 = 0.0f;
	m32 = 0.0f;
	m33 = 1.0f;
}