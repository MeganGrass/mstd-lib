/*
*
*	Megan Grass
*	April 12, 2024
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
	Point (w/ Color)
*/
struct vecpc
{
	vec3 vec;
	unsigned long color;
	float size;
};

/*
	Point (w/ Color and UV)
*/
struct vecpct
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
	Vertex (w/ Color)
*/
struct vec3c
{
	vec3 vec;
	unsigned long color;
};

/*
	Vertex (w/ Normal and Color)
*/
struct vec3cn
{
	vec3 vec;
	vec3 normal;
	unsigned long color;
};

/*
	Vertex (w/ Color and UV)
*/
struct vec3ct
{
	vec3 vec;
	unsigned long color;
	vec2 uv;
};

/*
	Vertex (w/ Normal, Color and UV)
*/
struct vec3cnt
{
	vec3 vec;
	vec3 normal;
	unsigned long color;
	vec2 uv;
};

#pragma pack(pop)