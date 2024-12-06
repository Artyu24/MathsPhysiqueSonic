#pragma once

#include <memory>
#include "Vector3.h"

class Box;

struct CollisionCallback3D
{
	std::shared_ptr<Box> box;
	Vector3f normal;
	float overlap;
	float restitution;
	Vector3f impactPoint;
};

