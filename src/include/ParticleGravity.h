#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public IParticleForceGenerator
{
	class Particle;

	public :
		ParticleGravity(float gravity);

	virtual void updateForce(Particle* particle, float duration);

	private :
		float m_gravity;
};

