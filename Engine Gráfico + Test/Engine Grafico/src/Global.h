#ifndef GLOBAL_H
#define GLOBAL_H

struct Color
{
	float R;
	float G;
	float B;
	float A;
};

struct CVec4
{
	float x;
	float y;
	float z;
	float w;
	Color color;
};

const Color RED = { 1.0, 0.0, 0.0, 1.0 };
const Color GREEN = { 0.0, 1.0, 0.0, 1.0 };
const Color BLUE = { 0.0, 0.0, 1.0, 1.0 };
const Color WHITE = { 1.0, 1.0, 1.0, 1.0 };
const Color BLACK = { 0.0, 0.0, 0.0, 1.0 };
#endif