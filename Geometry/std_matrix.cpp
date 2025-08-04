/*
*
*	Megan Grass
*	April 11, 2024
*
*/


#include "std_matrix.h"


Standard_Matrix Standard_Matrix::Translate(vec3 Vector) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m03 = Vector.x;
	Matrix.m13 = Vector.y;
	Matrix.m23 = Vector.z;
	*this *= Matrix;
	return *this;
}

Standard_Matrix Standard_Matrix::Scale(vec3 Vector) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = Vector.x;
	Matrix.m11 = Vector.y;
	Matrix.m22 = Vector.z;
	*this *= Matrix;
	return *this;
}

Standard_Matrix Standard_Matrix::Rotate(vec3 Vector) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Vector.y) * cosf(Vector.z);
	Matrix.m01 = cosf(Vector.y) * sinf(Vector.z);
	Matrix.m02 = sinf(Vector.y);
	Matrix.m10 = sinf(Vector.x) * sinf(Vector.y) * cosf(Vector.z) + cosf(Vector.x) * sinf(Vector.z);
	Matrix.m11 = sinf(Vector.x) * sinf(Vector.y) * sinf(Vector.z) - cosf(Vector.x) * cosf(Vector.z);
	Matrix.m12 = -sinf(Vector.x) * cosf(Vector.y);
	Matrix.m20 = -cosf(Vector.x) * sinf(Vector.y) * cosf(Vector.z) + sinf(Vector.x) * sinf(Vector.z);
	Matrix.m21 = -cosf(Vector.x) * sinf(Vector.y) * sinf(Vector.z) - sinf(Vector.x) * cosf(Vector.z);
	Matrix.m22 = cosf(Vector.x) * cosf(Vector.y);
	*this *= Matrix;
	return *this;
}

Standard_Matrix Standard_Matrix::RotateX(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m11 = cosf(Angle);
	Matrix.m12 = -sinf(Angle);
	Matrix.m21 = sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this *= Matrix;
	return *this;
}

Standard_Matrix Standard_Matrix::RotateY(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m02 = sinf(Angle);
	Matrix.m20 = -sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this *= Matrix;
	return *this;
}

Standard_Matrix Standard_Matrix::RotateZ(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m01 = -sinf(Angle);
	Matrix.m10 = sinf(Angle);
	Matrix.m11 = cosf(Angle);
	*this *= Matrix;
	return *this;
}

Standard_Matrix Standard_Matrix::YawPitchRoll(vec3 Vector) noexcept
{
	Standard_Matrix Matrix;
	
	float sy = sinf(Vector.y);
	float cy = cosf(Vector.y);
	float sp = sinf(Vector.x);
	float cp = cosf(Vector.x);
	float sr = sinf(Vector.z);
	float cr = cosf(Vector.z);

	Matrix.m00 = cr * cy + sr * sp * sy;
	Matrix.m01 = sr * cp;
	Matrix.m02 = cr * -sy + sr * sp * cy;

	Matrix.m10 = -sr * cy + cr * sp * sy;
	Matrix.m11 = cr * cp;
	Matrix.m12 = sr * sy + cr * sp * cy;

	Matrix.m20 = cp * sy;
	Matrix.m21 = -sp;
	Matrix.m22 = cp * cy;

	*this = Transpose(Matrix, *this);
	return *this;
}

Standard_Matrix Standard_Matrix::Pitch(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m11 = cosf(Angle);
	Matrix.m12 = -sinf(Angle);
	Matrix.m21 = sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this = Transpose(Matrix, *this);
	return *this;
}

Standard_Matrix Standard_Matrix::Yaw(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m02 = sinf(Angle);
	Matrix.m20 = -sinf(Angle);
	Matrix.m22 = cosf(Angle);
	*this = Transpose(Matrix, *this);
	return *this;
}

Standard_Matrix Standard_Matrix::Roll(float Angle) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m00 = cosf(Angle);
	Matrix.m01 = -sinf(Angle);
	Matrix.m10 = sinf(Angle);
	Matrix.m11 = cosf(Angle);
	*this = Transpose(Matrix, *this);
	return *this;
}

Standard_Matrix Standard_Matrix::Shear(vec3 Vector) noexcept
{
	Standard_Matrix Matrix;
	Matrix.m01 = Vector.x;
	Matrix.m02 = Vector.y;
	Matrix.m10 = Vector.z;
	Matrix.m12 = Vector.x;
	Matrix.m20 = Vector.y;
	Matrix.m21 = Vector.z;
	*this *= Matrix;
	return *this;
}

Standard_Matrix Standard_Matrix::Reflect(vec3 Vector) noexcept
{
	Standard_Matrix Matrix;
	Vector = Vector.Normalize();
	Matrix.m00 = 1.0f - 2.0f * Vector.x * Vector.x;
	Matrix.m11 = 1.0f - 2.0f * Vector.y * Vector.y;
	Matrix.m22 = 1.0f - 2.0f * Vector.z * Vector.z;
	Matrix.m01 = -2.0f * Vector.x * Vector.y;
	Matrix.m02 = -2.0f * Vector.x * Vector.z;
	Matrix.m10 = -2.0f * Vector.y * Vector.x;
	Matrix.m12 = -2.0f * Vector.y * Vector.z;
	Matrix.m20 = -2.0f * Vector.z * Vector.x;
	Matrix.m21 = -2.0f * Vector.z * Vector.y;
	*this *= Matrix;
	return *this;
}

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

Standard_Matrix Standard_Matrix::Dot(Standard_Matrix& m0, Standard_Matrix& m1) const noexcept
{
	Standard_Matrix Matrix;

	Matrix.m00 = m0.m00 * m1.m00 + m0.m01 * m1.m01 + m0.m02 * m1.m02 + m0.m03 * m1.m03;
	Matrix.m01 = m0.m10 * m1.m00 + m0.m11 * m1.m01 + m0.m12 * m1.m02 + m0.m13 * m1.m03;
	Matrix.m02 = m0.m20 * m1.m00 + m0.m21 * m1.m01 + m0.m22 * m1.m02 + m0.m23 * m1.m03;
	Matrix.m03 = m0.m30 * m1.m00 + m0.m31 * m1.m01 + m0.m32 * m1.m02 + m0.m33 * m1.m03;

	Matrix.m10 = m0.m00 * m1.m10 + m0.m01 * m1.m11 + m0.m02 * m1.m12 + m0.m03 * m1.m13;
	Matrix.m11 = m0.m10 * m1.m10 + m0.m11 * m1.m11 + m0.m12 * m1.m12 + m0.m13 * m1.m13;
	Matrix.m12 = m0.m20 * m1.m10 + m0.m21 * m1.m11 + m0.m22 * m1.m12 + m0.m23 * m1.m13;
	Matrix.m13 = m0.m30 * m1.m10 + m0.m31 * m1.m11 + m0.m32 * m1.m12 + m0.m33 * m1.m13;

	Matrix.m20 = m0.m00 * m1.m20 + m0.m01 * m1.m21 + m0.m02 * m1.m22 + m0.m03 * m1.m23;
	Matrix.m21 = m0.m10 * m1.m20 + m0.m11 * m1.m21 + m0.m12 * m1.m22 + m0.m13 * m1.m23;
	Matrix.m22 = m0.m20 * m1.m20 + m0.m21 * m1.m21 + m0.m22 * m1.m22 + m0.m23 * m1.m23;
	Matrix.m23 = m0.m30 * m1.m20 + m0.m31 * m1.m21 + m0.m32 * m1.m22 + m0.m33 * m1.m23;

	Matrix.m30 = m0.m00 * m1.m30 + m0.m01 * m1.m31 + m0.m02 * m1.m32 + m0.m03 * m1.m33;
	Matrix.m31 = m0.m10 * m1.m30 + m0.m11 * m1.m31 + m0.m12 * m1.m32 + m0.m13 * m1.m33;
	Matrix.m32 = m0.m20 * m1.m30 + m0.m21 * m1.m31 + m0.m22 * m1.m32 + m0.m23 * m1.m33;
	Matrix.m33 = m0.m30 * m1.m30 + m0.m31 * m1.m31 + m0.m32 * m1.m32 + m0.m33 * m1.m33;

	return Matrix;
}

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

Standard_Matrix Standard_Matrix::SetWorld(const vec3& mTranslation, const vec3& mRotation, const vec3& mScale) noexcept
{
	Standard_Matrix S = Standard_Matrix().Scale(mScale);
	Standard_Matrix R = Standard_Matrix().YawPitchRoll(vec3{ Radian(mRotation.x), Radian(mRotation.y), Radian(mRotation.z) });
	Standard_Matrix T = Standard_Matrix().Translate(mTranslation);
	*this = S * R * T;
	return *this;
}

Standard_Matrix Standard_Matrix::SetWorldCentroid(const vec3& mTranslation, const vec3& mRotation, const vec3& mCentroid, const vec3& mScale) noexcept
{
	Standard_Matrix Neg = Standard_Matrix().Translate(-mCentroid);
	Standard_Matrix Pos = Standard_Matrix().Translate(mCentroid);
	Standard_Matrix R = Standard_Matrix().YawPitchRoll(vec3{ Radian(mRotation.x), Radian(mRotation.y), Radian(mRotation.z) });
	Standard_Matrix T = Standard_Matrix().Translate(vec3{ mTranslation.x, mTranslation.y, mTranslation.z });
	*this = T * (Pos * R * Neg);
	return *this;
}

vec3 Standard_Matrix::Centroid(const std::vector<vec3>& Shape) const noexcept
{
	if (Shape.empty()) return vec3(0.0f, 0.0f, 0.0f);
	vec3 c(0.0f, 0.0f, 0.0f);
	for (const auto& v : Shape) { c += v; }
	c /= (float)(Shape.size());
	return c;
}

vec3 Standard_Matrix::Centroid(const std::vector<vec3>& Shape, const vec3& Pos) const noexcept
{
	if (Shape.empty()) return vec3(0.0f, 0.0f, 0.0f);
	vec3 c(0.0f, 0.0f, 0.0f);
	for (const auto& v : Shape) { c += v; }
	c /= (float)(Shape.size());
	c += Pos;
	return c;
}

void Standard_Matrix::VecTransform(vec3& Vec) const noexcept
{
	Vec.x = Vec.x * m00 + Vec.y * m01 + Vec.z * m02 + 1.0f * m03;
	Vec.y = Vec.x * m10 + Vec.y * m11 + Vec.z * m12 + 1.0f * m13;
	Vec.z = Vec.x * m20 + Vec.y * m21 + Vec.z * m22 + 1.0f * m23;
	float w = Vec.x * m30 + Vec.y * m31 + Vec.z * m32 + 1.0f * m33;
	if (w != 0.0f && w != 1.0f)
	{
		Vec.x /= w;
		Vec.y /= w;
		Vec.z /= w;
	}
}

void Standard_Matrix::VecTransform(vec4& Vec) const noexcept
{
	Vec.x = Vec.x * m00 + Vec.y * m01 + Vec.z * m02 + Vec.w * m03;
	Vec.y = Vec.x * m10 + Vec.y * m11 + Vec.z * m12 + Vec.w * m13;
	Vec.z = Vec.x * m20 + Vec.y * m21 + Vec.z * m22 + Vec.w * m23;
	Vec.w = Vec.x * m30 + Vec.y * m31 + Vec.z * m32 + Vec.w * m33;
	if (Vec.w != 0.0f && Vec.w != 1.0f)
	{
		Vec.x /= Vec.w;
		Vec.y /= Vec.w;
		Vec.z /= Vec.w;
	}
}

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

void Standard_Matrix::OrthogonalOffCenterLeft(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f / (Right - Left);
	m11 = 2.0f / (Top - Bottom);
	m22 = 1.0f / (zFar - zNear);
	m03 = (Left + Right) / (Left - Right);
	m13 = (Top + Bottom) / (Bottom - Top);
	m23 = zNear / (zNear - zFar);
	m33 = 1.0f;

	m01 = m02 = m10 = m12 = m20 = m21 = m30 = m31 = m32 = 0.0f;
}

void Standard_Matrix::OrthogonalOffCenterRight(float Left, float Right, float Bottom, float Top, float zNear, float zFar) noexcept
{
	Identity();
	m00 = 2.0f / (Right - Left);
	m11 = 2.0f / (Top - Bottom);
	m22 = 1.0f / (zNear - zFar);
	m03 = (Left + Right) / (Left - Right);
	m13 = (Top + Bottom) / (Bottom - Top);
	m23 = zNear / (zNear - zFar);
	m33 = 1.0f;

	m01 = m02 = m10 = m12 = m20 = m21 = m30 = m31 = m32 = 0.0f;
}

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

void Standard_Matrix::LookAtLeft(const vec3& Eye, const vec3& At, const vec3& Up) noexcept
{
	vec3 Z = (At - Eye).Normalize();
	vec3 X = Up.Cross(Z).Normalize();
	vec3 Y = Z.Cross(X);

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

void Standard_Matrix::LookAtRight(const vec3& Eye, const vec3& At, const vec3& Up) noexcept
{
	vec3 Z = (Eye - At).Normalize();
	vec3 X = Up.Cross(Z).Normalize();
	vec3 Y = Z.Cross(X);

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