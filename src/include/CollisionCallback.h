#pragma once

#include <memory>
#include "Vector3.h"

class Box;

struct CollisionCallback
{
	explicit CollisionCallback(std::shared_ptr<Box> boxptr, Vector3f colnormal, float coloverlap, float colrestitution = 1.f) :
	box(boxptr),
	normal(colnormal),
	overlap(coloverlap),
	restitution(colrestitution)
	{
	}

	std::shared_ptr<Box> box;
	Vector3f normal;
	float overlap;
	float restitution;
};

