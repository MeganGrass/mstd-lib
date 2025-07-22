/*
*
*	Megan Grass
*	November 13, 2024
*
*/


#pragma once

#include <cmath>

#include <cstdint>

#include <utility>

#include <iostream>

/*
	Vector
*/
class vec3 {
private:

public:

	// Data
	float x, y, z;

	vec3(void) noexcept : x(0.0f), y(0.0f), z(0.0f) {}
	vec3(float X, float Y, float Z) noexcept : x(X), y(Y), z(Z) {}
	vec3(std::int32_t X, std::int32_t Y, std::int32_t Z) noexcept : x(static_cast<float>(X)), y(static_cast<float>(Y)), z(static_cast<float>(Z)) {}

	// Copy
	vec3(const vec3& v) noexcept : x(v.x), y(v.y), z(v.z) {}
	vec3& operator = (const vec3& v) noexcept { return *this = vec3(v); }

	// Move
	vec3(vec3&& v) noexcept : x(std::exchange(v.x, 0.0f)), y(std::exchange(v.y, 0.0f)), z(std::exchange(v.z, 0.0f)) {}
	vec3& operator = (vec3&& v) noexcept { std::swap(x, v.x); std::swap(y, v.y); std::swap(z, v.z); return *this; }

	// Get Integral X
	[[nodiscard]] std::int32_t GetX(void) const noexcept { return static_cast<std::int32_t>(std::round(x)); }

	// Get Integral Y
	[[nodiscard]] std::int32_t GetY(void) const noexcept { return static_cast<std::int32_t>(std::round(y)); }

	// Get Integral Z
	[[nodiscard]] std::int32_t GetZ(void) const noexcept { return static_cast<std::int32_t>(std::round(z)); }

	// Unary
	vec3 operator - (void) const noexcept { return vec3(-x, -y, -z); }

	// Equality
	bool operator == (const vec3& v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	bool operator != (const vec3& v) const noexcept { return !(*this == v); }

	// Addition
	vec3 operator + (const vec3& v) const noexcept { return vec3(x + v.x, y + v.y, z + v.z); }
	vec3& operator += (const vec3& v) noexcept { return *this = *this + v; }

	// Scalar Addition
	vec3 operator + (float s) const noexcept { return vec3(x + s, y + s, z + s); }
	vec3& operator += (float s) noexcept { return *this = *this + s; }

	// Subtraction
	vec3 operator - (const vec3& v) const noexcept { return vec3(x - v.x, y - v.y, z - v.z); }
	vec3& operator -= (const vec3& v) noexcept { return *this = *this - v; }

	// Scalar Subtraction
	vec3 operator - (float s) const noexcept { return vec3(x - s, y - s, z - s); }
	vec3& operator -= (float s) noexcept { return *this = *this - s; }

	// Multiplication
	vec3 operator * (const vec3& v) const noexcept { return vec3(x * v.x, y * v.y, z * v.z); }
	vec3& operator *= (const vec3& v) noexcept { return *this = *this * v; }

	// Scalar Multiplication
	vec3 operator * (float s) const noexcept { return vec3(x * s, y * s, z * s); }
	vec3& operator *= (float s) noexcept { return *this = *this * s; }

	// Division
	vec3 operator / (const vec3& v) const noexcept { return vec3(x / v.x, y / v.y, z / v.z); }
	vec3& operator /= (const vec3& v) noexcept { return *this = *this / v; }

	// Scalar Division
	vec3 operator / (float s) const noexcept { return vec3(x / s, y / s, z / s); }
	vec3& operator /= (float s) noexcept { return *this = *this / s; }

	// Set
	void Set(float X, float Y, float Z) noexcept { x = X; y = Y; z = Z; }

	// Set
	void Set(const vec3& v) noexcept { x = v.x; y = v.y; z = v.z; }

	// Scale
	void Scale(float S) noexcept { x *= S; y *= S; z *= S; }

	// Scale
	void Scale(float X, float Y, float Z) noexcept { x *= X; y *= Y; z *= Z; }

	// Scale
	void Scale(const vec3& v) noexcept { x *= v.x; y *= v.y; z *= v.z; }

	// Length
	float Length(void) const noexcept { return sqrtf(x * x + y * y + z * z); }

	// Dot
	float Dot(const vec3& v) const noexcept { return x * v.x + y * v.y + z * v.z; }

	// Cross
	vec3 Cross(const vec3& v) const noexcept { return vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }

	// Lerp
	vec3 Lerp(const vec3& v0, const vec3& v1, float t) const noexcept { return vec3(std::lerp(v0.x, v1.x, t), std::lerp(v0.y, v1.y, t), std::lerp(v0.z, v1.z, t)); }

	// Lerp
	vec3 Lerp(const vec3& v, float t) noexcept { return *this = Lerp(*this, v, t); }

	// Normalize
	vec3 Normalize(void) const noexcept
	{
		float Len = Length();
		if (Len == 0.0f)
		{
			std::cout << "Cannot normalize a vector with length 0" << std::endl;
			return vec3(0.0f, 0.0f, 0.0f);
		}
		Len = 1.0f / Len;
		return vec3(x * Len, y * Len, z * Len);
	}

	// Rotate
	vec3 Rotate(float Angle, float X, float Y, float Z) const noexcept
	{
		float s = sinf(Angle);
		float c = cosf(Angle);
		float dx = x - X;
		float dy = y - Y;
		float dz = z - Z;
		return vec3(X + dx * c - dy * s, Y + dx * s + dy * c, Z + dz);
	}

	// Rotate X
	void RotateX(float Angle) noexcept
	{
		float s = sinf(Angle);
		float c = cosf(Angle);
		float ty = y;
		y = y * c - z * s;
		z = ty * s + z * c;
	}

	// Rotate Y
	void RotateY(float Angle) noexcept
	{
		float s = sinf(Angle);
		float c = cosf(Angle);
		float tx = x;
		x = x * c - z * s;
		z = tx * s + z * c;
	}

	// Rotate Z
	void RotateZ(float Angle) noexcept
	{
		float s = sinf(Angle);
		float c = cosf(Angle);
		float tx = x;
		x = x * c - y * s;
		y = tx * s + y * c;
	}

};