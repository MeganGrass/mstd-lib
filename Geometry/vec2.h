/*
*
*	Megan Grass
*	November 13, 2024
*
*
*	TODO:
*
*/


#pragma once

#include <cmath>

#include <cstdint>

#include <utility>

#include <iostream>

/*
	Vector 2D
*/
class vec2 {
private:

public:

	/*
		Data
	*/
	float x, y;

	/*
		Construction
	*/
	explicit vec2(void) noexcept : x(0.0f), y(0.0f) {}
	explicit vec2(float X, float Y) noexcept : x(X), y(Y) {}
	explicit vec2(std::int32_t X, std::int32_t Y) noexcept : x(static_cast<float>(X)), y(static_cast<float>(Y)) {}

	/*
		Copy
	*/
	vec2(const vec2& v) noexcept : x(v.x), y(v.y) {}
	vec2& operator = (const vec2& v) noexcept { return *this = vec2(v); }

	/*
		Move
	*/
	vec2(vec2&& v) noexcept : x(std::exchange(v.x, 0.0f)), y(std::exchange(v.y, 0.0f)) {}
	vec2& operator = (vec2&& v) noexcept
	{
		std::swap(x, v.x);
		std::swap(y, v.y);
		return *this;
	}

	/*
		Unary
	*/
	vec2 operator - (void) const noexcept { return vec2(-x, -y); }

	/*
		Equality
	*/
	bool operator == (const vec2& v) const noexcept { return x == v.x && y == v.y; }
	bool operator != (const vec2& v) const noexcept { return !(*this == v); }

	/*
		Addition
	*/
	vec2 operator + (const vec2& v) const noexcept { return vec2(x + v.x, y + v.y); }
	vec2& operator += (const vec2& v) noexcept { return *this = *this + v; }

	/*
		Scalar Addition
	*/
	vec2 operator + (float s) const noexcept { return vec2(x + s, y + s); }
	vec2& operator += (float s) noexcept { return *this = *this + s; }

	/*
		Subtraction
	*/
	vec2 operator - (const vec2& v) const noexcept { return vec2(x - v.x, y - v.y); }
	vec2& operator -= (const vec2& v) noexcept { return *this = *this - v; }

	/*
		Scalar Subtraction
	*/
	vec2 operator - (float s) const noexcept { return vec2(x - s, y - s); }
	vec2& operator -= (float s) noexcept { return *this = *this - s; }

	/*
		Multiplication
	*/
	vec2 operator * (const vec2& v) const noexcept { return vec2(x * v.x, y * v.y); }
	vec2& operator *= (const vec2& v) noexcept { return *this = *this * v; }

	/*
		Scalar Multiplication
	*/
	vec2 operator * (float s) const noexcept { return vec2(x * s, y * s); }
	vec2& operator *= (float s) noexcept { return *this = *this * s; }

	/*
		Division
	*/
	vec2 operator / (const vec2& v) const noexcept { return vec2(x / v.x, y / v.y); }
	vec2& operator /= (const vec2& v) noexcept { return *this = *this / v; }

	/*
		Scalar Division
	*/
	vec2 operator / (float s) const noexcept { return vec2(x / s, y / s); }
	vec2& operator /= (float s) noexcept { return *this = *this / s; }

	/*
		Integral
	*/
	[[nodiscard]] std::int32_t GetX(void) const noexcept { return static_cast<std::int32_t>(std::round(x)); }
	[[nodiscard]] std::int32_t GetY(void) const noexcept { return static_cast<std::int32_t>(std::round(y)); }

	/*
		Set
	*/
	void Set(float X, float Y) noexcept { x = X; y = Y; }

	/*
		Set
	*/
	void Set(const vec2& v) noexcept { x = v.x; y = v.y; }

	/*
		Scale
	*/
	void Scale(float S) noexcept { x *= S; y *= S; }

	/*
		Scale
	*/
	void Scale(float X, float Y, float Z) noexcept { x *= X; y *= Y; }

	/*
		Scale
	*/
	void Scale(const vec2& v) noexcept { x *= v.x; y *= v.y; }

	/*
		Length 2D
	*/
	float Length(void) const noexcept { return sqrtf(x * x + y * y); }

	/*
		Dot
	*/
	float Dot(const vec2& v) const noexcept { return x * v.x + y * v.y; }

	/*
		Cross
	*/
	vec2 Cross(const vec2& v) const noexcept { return vec2(y * v.x - x * v.y, x * v.y - y * v.x); }

	/*
		Lerp
	*/
	vec2 Lerp(const vec2& v0, const vec2& v1, float t) const noexcept { return vec2(std::lerp(v0.x, v1.x, t), std::lerp(v0.y, v1.y, t)); }

	/*
		Lerp
	*/
	vec2 Lerp(const vec2& v, float t) noexcept { return *this = Lerp(*this, v, t); }

	/*
		Normalize
	*/
	vec2 Normalize(void) const noexcept
	{
		float Len = Length();
		if (Len == 0.0f)
		{
			std::cout << "Cannot normalize a vector with length 0" << std::endl;
			return vec2(0.0f, 0.0f);
		}
		Len = 1.0f / Len;
		return vec2(x * Len, y * Len);
	}

	/*
		Rotate
	*/
	vec2 Rotate(float Angle, float X, float Y) const noexcept
	{
		float s = sinf(Angle);
		float c = cosf(Angle);
		float dx = x - X;
		float dy = y - Y;
		return vec2(X + dx * c - dy * s, Y + dx * s + dy * c);
	}

};