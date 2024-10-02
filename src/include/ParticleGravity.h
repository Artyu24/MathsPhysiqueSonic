#pragma once
#include "ParticuleForceGenerator.h"

class ParticleGravity : public IParticuleForceGenerator
{
	class Particle;

	public :
		ParticleGravity(float gravity);

	virtual void updateForce(Particle* particle, float duration);

	private :
		float m_gravity;
};

