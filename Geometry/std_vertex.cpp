/*
*
*	Megan Grass
*	April 12, 2024
*
*
*	TODO:
*
*/


#include "std_vertex.h"


/*
	Normalize 2D
*/
Standard_Vertex Standard_Vertex::Normalize2D(void) const noexcept
{
	float Len = Length2D();
	if (Len == 0.0f)
	{
		std::cout << "Cannot normalize a vector with length 0" << std::endl;
		return Standard_Vertex();
	}
	Len = 1.0f / Len;
	return Standard_Vertex(x * Len, y * Len, 0.0f);
}


/*
	Normalize
*/
Standard_Vertex Standard_Vertex::Normalize(void) const noexcept
{
	float Len = Length();
	if (Len == 0.0f)
	{
		std::cout << "Cannot normalize a vector with length 0" << std::endl;
		return Standard_Vertex();
	}
	Len = 1.0f / Len;
	return Standard_Vertex(x * Len, y * Len, z * Len);
}


/*
	Normalize W
*/
Standard_Vertex Standard_Vertex::NormalizeW(void) const noexcept
{
	float Len = LengthW();
	if (Len == 0.0f)
	{
		std::cout << "Cannot normalize a vector with length 0" << std::endl;
		return Standard_Vertex();
	}
	Len = 1.0f / Len;
	return Standard_Vertex(x * Len, y * Len, z * Len, w * Len);
}


/*
	Rotate 2D
*/
Standard_Vertex Standard_Vertex::Rotate2D(float cx, float cy, float angle) const noexcept
{
	float s = sinf(angle);
	float c = cosf(angle);
	float dx = x - cx;
	float dy = y - cy;
	return Standard_Vertex(cx + dx * c - dy * s, cy + dx * s + dy * c, 0.0f);
}


/*
	Rotate
*/
Standard_Vertex Standard_Vertex::Rotate(float cx, float cy, float cz, float angle) const noexcept
{
	float s = sinf(angle);
	float c = cosf(angle);
	float dx = x - cx;
	float dy = y - cy;
	float dz = z - cz;
	return Standard_Vertex(cx + dx * c - dy * s, cy + dx * s + dy * c, cz + dz, 0.0f);
}


/*
	Rotate W
*/
Standard_Vertex Standard_Vertex::RotateW(float cx, float cy, float cz, float cw, float angle) const noexcept
{
	float s = sinf(angle);
	float c = cosf(angle);
	float dx = x - cx;
	float dy = y - cy;
	float dz = z - cz;
	float dw = w - cw;
	return Standard_Vertex(cx + dx * c - dy * s, cy + dx * s + dy * c, cz + dz, cw + dw);
}


/*
	Rotate X
*/
void Standard_Vertex::RotateX(float angle) noexcept
{
	float s = sinf(x);
	float c = cosf(x);
	float dy = y - angle;
	y = angle + dy * c - z * s;
	z = angle + dy * s + z * c;
}


/*
	Rotate Y
*/
void Standard_Vertex::RotateY(float angle) noexcept
{
	float s = sinf(y);
	float c = cosf(y);
	float dx = x - angle;
	x = angle + dx * c - z * s;
	z = angle + dx * s + z * c;
}


/*
	Rotate Z
*/
void Standard_Vertex::RotateZ(float angle) noexcept
{
	float s = sinf(z);
	float c = cosf(z);
	float dx = x - angle;
	x = angle + dx * c - y * s;
	y = angle + dx * s + y * c;
}