#pragma once
#include "ParticleForceGenerator.h"


class ParticleFrictionCinetique : public IParticleForceGenerator
{
	class Particle;

public:
	ParticleFrictionCinetique();

	virtual void UpdateForce(Particle* particle, float duration);
};

