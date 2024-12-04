#pragma once
#include "Vector3.h"

class Area
{
public:
	Area();
	Area(Vector3f pos, float sideSize);

	Vector3f pos;
	float sideSize;
};

