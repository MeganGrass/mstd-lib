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
	Vector W
*/
class vec4 {
private:

public:

	// Data
	float x, y, z, w;

	explicit vec4(void) noexcept : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	explicit vec4(float X, float Y, float Z, float W) noexcept : x(X), y(Y), z(Z), w(W) {}
	explicit vec4(int32_t X, int32_t Y, int32_t Z, int32_t W) noexcept : x(static_cast<float>(X)), y(static_cast<float>(Y)), z(static_cast<float>(Z)), w(static_cast<float>(W)) {}

	// Copy
	vec4(const vec4& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}
	vec4& operator = (const vec4& v) noexcept { return *this = vec4(v); }

	// Move
	vec4(vec4&& v) noexcept : x(std::exchange(v.x, 0.0f)), y(std::exchange(v.y, 0.0f)), z(std::exchange(v.z, 0.0f)), w(std::exchange(v.w, 0.0f)) {}
	vec4& operator = (vec4&& v) noexcept { std::swap(x, v.x); std::swap(y, v.y); std::swap(z, v.z); std::swap(w, v.w); return *this; }

	// Get Integral X
	[[nodiscard]] std::int32_t GetX(void) const noexcept { return static_cast<std::int32_t>(std::round(x)); }

	// Get Integral Y
	[[nodiscard]] std::int32_t GetY(void) const noexcept { return static_cast<std::int32_t>(std::round(y)); }

	// Get Integral Z
	[[nodiscard]] std::int32_t GetZ(void) const noexcept { return static_cast<std::int32_t>(std::round(z)); }

	// Get Integral W
	[[nodiscard]] std::int32_t GetW(void) const noexcept { return static_cast<std::int32_t>(std::round(w)); }

	// Unary
	vec4 operator - (void) const noexcept { return vec4(-x, -y, -z, -w); }

	// Equality
	bool operator == (const vec4& v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator != (const vec4& v) const noexcept { return !(*this == v); }

	// Addition
	vec4 operator + (const vec4& v) const noexcept { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
	vec4& operator += (const vec4& v) noexcept { return *this = *this + v; }

	// Scalar Addition
	vec4 operator + (float s) const noexcept { return vec4(x + s, y + s, z + s, w + s); }
	vec4& operator += (float s) noexcept { return *this = *this + s; }

	// Subtraction
	vec4 operator - (const vec4& v) const noexcept { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
	vec4& operator -= (const vec4& v) noexcept { return *this = *this - v; }

	// Scalar Subtraction
	vec4 operator - (float s) const noexcept { return vec4(x - s, y - s, z - s, w - s); }
	vec4& operator -= (float s) noexcept { return *this = *this - s; }

	// Multiplication
	vec4 operator * (const vec4& v) const noexcept { return vec4(x * v.x, y * v.y, z * v.z, w * v.w); }
	vec4& operator *= (const vec4& v) noexcept { return *this = *this * v; }

	// Scalar Multiplication
	vec4 operator * (float s) const noexcept { return vec4(x * s, y * s, z * s, w * s); }
	vec4& operator *= (float s) noexcept { return *this = *this * s; }

	// Division
	vec4 operator / (const vec4& v) const noexcept { return vec4(x / v.x, y / v.y, z / v.z, w / v.w); }
	vec4& operator /= (const vec4& v) noexcept { return *this = *this / v; }

	// Scalar Division
	vec4 operator / (float s) const noexcept { return vec4(x / s, y / s, z / s, w / s); }
	vec4& operator /= (float s) noexcept { return *this = *this / s; }

	// Set
	void Set(float X, float Y, float Z, float W) noexcept { x = X; y = Y; z = Z; w = W; }

	// Set
	void Set(const vec4& v) noexcept { x = v.x; y = v.y; z = v.z; w = v.w; }

	// Scale
	void Scale(float S) noexcept { x *= S; y *= S; z *= S; }

	// Scale
	void Scale(float X, float Y, float Z) noexcept { x *= X; y *= Y; z *= Z; }

	// Scale
	void Scale(const vec3& v) noexcept { x *= v.x; y *= v.y; z *= v.z; }

	// Scale
	void Scale(const vec4& v) noexcept { x *= v.x; y *= v.y; z *= v.z; }

	// Length
	float Length(void) const noexcept { return sqrtf(x * x + y * y + z * z); }

	// Dot
	float Dot(const vec3& v) const noexcept { return x * v.x + y * v.y + z * v.z; }

	// Dot
	float Dot(const vec4& v) const noexcept { return x * v.x + y * v.y + z * v.z; }

	// Cross
	vec4 Cross(const vec3& v) const noexcept { return vec4(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, w); }

	// Cross
	vec4 Cross(const vec4& v) const noexcept { return vec4(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, w); }

	// Lerp
	vec4 Lerp(const vec4& v0, const vec4& v1, float t) const noexcept { return vec4(std::lerp(v0.x, v1.x, t), std::lerp(v0.y, v1.y, t), std::lerp(v0.z, v1.z, t), w); }

	// Lerp
	vec4 Lerp(const vec4& v, float t) noexcept { return *this = Lerp(*this, v, t); }

	// Normalize
	vec4 Normalize(void) const noexcept
	{
		float Len = Length();
		if (Len == 0.0f)
		{
			std::cout << "Cannot normalize a vector with length 0" << std::endl;
			return vec4(0.0f, 0.0f, 0.0f, 0.0f);
		}
		Len = 1.0f / Len;
		return vec4(x * Len, y * Len, z * Len, w);
	}

};