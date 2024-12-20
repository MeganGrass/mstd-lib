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

#pragma pack(push, 1)

/*
	Vector 2D
*/
#include "vec2.h"

/*
	Vector
*/
#include "vec3.h"

/*
	Vector W
*/
#include "vec4.h"

/*
	Point
*/
struct vecp
{
	vec3 vec;
	float size;
};

/*
	Point (Gouraud-shaded)
*/
struct vecpg
{
	vec3 vec;
	unsigned long color;
	float size;
};

/*
	Point (Gouraud-shaded w/ UV)
*/
struct vecpgt
{
	vec3 vec;
	unsigned long color;
	float size;
	vec2 uv;
};

/*
	Texture
*/
struct vec3t
{
	vec3 vec;
	vec2 uv;
};

/*
	Texture W
*/
struct vec4t
{
	vec4 vec;
	vec2 uv;
};

/*
	Vertex (w/ Normal)
*/
struct vec3n
{
	vec3 vec;
	vec3 normal;
};

/*
	Vertex (w/ Normal and UV)
*/
struct vec3nt
{
	vec3 vec;
	vec3 normal;
	vec2 uv;
};

/*
	Vertex (Gouraud-shaded)
*/
struct vec3g
{
	vec3 vec;
	unsigned long color;
};

/*
	Vertex (Gouraud-shaded w/ Normal)
*/
struct vec3gn
{
	vec3 vec;
	vec3 normal;
	unsigned long color;
};

/*
	Vertex (Gouraud-shaded w/ UV)
*/
struct vec3gt
{
	vec3 vec;
	unsigned long color;
	vec2 uv;
};

/*
	Vertex (Gouraud-shaded w/ Normal and UV)
*/
struct vec3gnt
{
	vec3 vec;
	vec3 normal;
	unsigned long color;
	vec2 uv;
};

#pragma pack(pop)