/*
*
*	Megan Grass
*	April 12, 2024
*
*
*	TODO:
*
*/


#pragma once

#include "../std_exception.h"


#pragma pack(push, 1)

struct vec2
{
	float x, y;
	void Set(float X, float Y) noexcept { x = X; y = Y; }
};

struct vec3
{
	float x, y, z;
	void Set(float X, float Y, float Z) noexcept { x = X; y = Y; z = Z; }
};

struct vec4
{
	float x, y, z, w;
	void Set(float X, float Y, float Z, float W) noexcept { x = X; y = Y; z = Z; w = W; }
};

struct vec3g
{
	vec3 pos;
	unsigned long color;
};

struct vec3gn
{
	vec3 pos;
	vec3 norm;
	unsigned long color;
};

struct vec3gnt
{
	vec3 pos;
	vec3 norm;
	unsigned long color;
	vec2 uv;
};

struct vec3t
{
	vec3 pos;
	vec2 uv;
};

struct vec4t
{
	vec4 pos;
	vec2 uv;
};

#pragma pack(pop)


typedef class Standard_Vertex StdVert;


/*
	Standard Vertex
*/
class Standard_Vertex {
private:

public:

	/*
		Data
	*/
	float x, y, z, w;

	/*
		Construction
	*/
	explicit Standard_Vertex(void) noexcept : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	explicit Standard_Vertex(float X, float Y, float Z, float W = 0.0f) noexcept : x(X), y(Y), z(Z), w(W) {}
	explicit Standard_Vertex(int32_t X, int32_t Y, int32_t Z, int32_t W = 0) noexcept : x(static_cast<float>(X)), y(static_cast<float>(Y)), z(static_cast<float>(Z)), w(static_cast<float>(W)) {}
	explicit Standard_Vertex(vec2 v) noexcept : x(v.x), y(v.y), z(0.0f), w(0.0f) {}
	explicit Standard_Vertex(vec3 v) noexcept : x(v.x), y(v.y), z(v.z), w(0.0f) {}
	explicit Standard_Vertex(vec4 v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}

	/*
		Copy
	*/
	Standard_Vertex(const Standard_Vertex& v) noexcept : x(v.x), y(v.y), z(v.z), w(v.w) {}
	Standard_Vertex& operator = (const Standard_Vertex& v) noexcept { return *this = Standard_Vertex(v); }

	/*
		Move
	*/
	Standard_Vertex(Standard_Vertex&& v) noexcept : x(std::exchange(v.x, 0.0f)), y(std::exchange(v.y, 0.0f)), z(std::exchange(v.z, 0.0f)), w(std::exchange(v.w, 0.0f)) {}
	Standard_Vertex& operator = (Standard_Vertex&& v) noexcept
	{
		std::swap(x, v.x);
		std::swap(y, v.y);
		std::swap(z, v.z);
		std::swap(w, v.w);
		return *this;
	}

	/*
		Unary
	*/
	Standard_Vertex operator - (void) const noexcept { return Standard_Vertex(-x, -y, -z, -w); }

	/*
		Equality
	*/
	bool operator == (const Standard_Vertex& v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	bool operator != (const Standard_Vertex& v) const noexcept { return !(*this == v); }

	/*
		Addition
	*/
	Standard_Vertex operator + (const Standard_Vertex& v) const noexcept { return Standard_Vertex(x + v.x, y + v.y, z + v.z, w + v.w); }
	Standard_Vertex& operator += (const Standard_Vertex& v) noexcept { return *this = *this + v; }

	/*
		Scalar Addition
	*/
	Standard_Vertex operator + (float s) const noexcept { return Standard_Vertex(x + s, y + s, z + s, w + s); }
	Standard_Vertex& operator += (float s) noexcept { return *this = *this + s; }

	/*
		Subtraction
	*/
	Standard_Vertex operator - (const Standard_Vertex& v) const noexcept { return Standard_Vertex(x - v.x, y - v.y, z - v.z, w - v.w); }
	Standard_Vertex& operator -= (const Standard_Vertex& v) noexcept { return *this = *this - v; }

	/*
		Scalar Subtraction
	*/
	Standard_Vertex operator - (float s) const noexcept { return Standard_Vertex(x - s, y - s, z - s, w - s); }
	Standard_Vertex& operator -= (float s) noexcept { return *this = *this - s; }

	/*
		Multiplication
	*/
	Standard_Vertex operator * (const Standard_Vertex& v) const noexcept { return Standard_Vertex(x * v.x, y * v.y, z * v.z, w * v.w); }
	Standard_Vertex& operator *= (const Standard_Vertex& v) noexcept { return *this = *this * v; }

	/*
		Scalar Multiplication
	*/
	Standard_Vertex operator * (float s) const noexcept { return Standard_Vertex(x * s, y * s, z * s, w * s); }
	Standard_Vertex& operator *= (float s) noexcept { return *this = *this * s; }

	/*
		Division
	*/
	Standard_Vertex operator / (const Standard_Vertex& v) const noexcept { return Standard_Vertex(x / v.x, y / v.y, z / v.z, w / v.w); }
	Standard_Vertex& operator /= (const Standard_Vertex& v) noexcept { return *this = *this / v; }

	/*
		Scalar Division
	*/
	Standard_Vertex operator / (float s) const noexcept { return Standard_Vertex(x / s, y / s, z / s, w / s); }
	Standard_Vertex& operator /= (float s) noexcept { return *this = *this / s; }

	/*
		Integral
	*/
	std::int32_t IntX(void) const noexcept { return static_cast<std::int32_t>(std::round(x)); }
	std::int32_t IntY(void) const noexcept { return static_cast<std::int32_t>(std::round(y)); }
	std::int32_t IntZ(void) const noexcept { return static_cast<std::int32_t>(std::round(z)); }
	std::int32_t IntW(void) const noexcept { return static_cast<std::int32_t>(std::round(w)); }

	/*
		Data
	*/
	float* data(void) const noexcept { return (float*)this; }

	/*
		Set
	*/
	void Set(float X, float Y, float Z = 0.0f, float W = 0.0f) noexcept { x = X; y = Y; z = Z; w = W; }

	/*
		Get vec2
	*/
	vec2 GetVec2(void) const noexcept { return { x, y }; }

	/*
		Get vec3
	*/
	vec3 GetVec3(void) const noexcept { return { x, y, z }; }

	/*
		Get vec4
	*/
	vec4 GetVec4(void) const noexcept { return { x, y, z, w }; }

	/*
		Scale
	*/
	void Scale(float S) noexcept { x *= S; y *= S; z *= S; }

	/*
		Scale
	*/
	void Scale(float X, float Y, float Z) noexcept { x *= X; y *= Y; z *= Z; }

	/*
		Scale
	*/
	void Scale(const Standard_Vertex& v) noexcept { x *= v.x; y *= v.y; z *= v.z; }

	/*
		Length 2D
	*/
	float Length2D(void) const noexcept { return sqrtf(x * x + y * y); }

	/*
		Length
	*/
	float Length(void) const noexcept { return sqrtf(x * x + y * y + z * z); }

	/*
		Length W
	*/
	float LengthW(void) const noexcept { return sqrtf(x * x + y * y + z * z + w * w); }

	/*
		Dot 2D
	*/
	float Dot2D(const Standard_Vertex& v) const noexcept { return x * v.x + y * v.y; }

	/*
		Dot
	*/
	float Dot(const Standard_Vertex& v) const noexcept { return x * v.x + y * v.y + z * v.z; }

	/*
		Dot W
	*/
	float DotW(const Standard_Vertex& v) const noexcept { return x * v.x + y * v.y + z * v.z + w * v.w; }

	/*
		Delta 2D
	*/
	float Delta2D(const Standard_Vertex& v) const noexcept { return (*this - v).Length2D(); }

	/*
		Delta
	*/
	float Delta(const Standard_Vertex& v) const noexcept { return (*this - v).Length(); }

	/*
		Delta W
	*/
	float DeltaW(const Standard_Vertex& v) const noexcept { return (*this - v).LengthW(); }

	/*
		Cross
	*/
	Standard_Vertex Cross(const Standard_Vertex& v) const noexcept { return Standard_Vertex(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x, w); }

	/*
		Normalize 2D
	*/
	Standard_Vertex Normalize2D(void) const noexcept;

	/*
		Normalize
	*/
	Standard_Vertex Normalize(void) const noexcept;

	/*
		Normalize W
	*/
	Standard_Vertex NormalizeW(void) const noexcept;

	/*
		Lerp
	*/
	Standard_Vertex Lerp(const Standard_Vertex& v0, const Standard_Vertex& v1, float t) const noexcept { return Standard_Vertex(std::lerp(v0.x, v1.x, t), std::lerp(v0.y, v1.y, t), std::lerp(v0.z, v1.z, t), std::lerp(v0.w, v1.w, t)); }

	/*
		Lerp
	*/
	Standard_Vertex Lerp(const Standard_Vertex& v, float t) noexcept { return *this = Lerp(*this, v, t); }

	/*
		Rotate 2D
	*/
	Standard_Vertex Rotate2D(float cx, float cy, float angle) const noexcept;

	/*
		Rotate
	*/
	Standard_Vertex Rotate(float cx, float cy, float cz, float angle) const noexcept;

	/*
		Rotate W
	*/
	Standard_Vertex RotateW(float cx, float cy, float cz, float cw, float angle) const noexcept;

	/*
		Rotate X
	*/
	void RotateX(float angle) noexcept;

	/*
		Rotate Y
	*/
	void RotateY(float angle) noexcept;

	/*
		Rotate Z
	*/
	void RotateZ(float angle) noexcept;

};