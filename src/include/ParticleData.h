#pragma once
#include "Vector3.h"

struct ParticleData
{
	ParticleData(Vector3f vel, float mass) : initialVelocity(vel), mass(mass) {}
	Vector3f initialVelocity;
	float mass;
};

