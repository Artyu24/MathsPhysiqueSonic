#pragma once
#include "ParticleForceGenerator.h"

class ParticleFrictionStatic : public IParticleForceGenerator
{
	class Particle;

public:
	ParticleFrictionStatic();

	virtual void UpdateForce(Particle* particle, float duration);
};

