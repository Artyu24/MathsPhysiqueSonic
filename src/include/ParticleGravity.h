#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public IParticleForceGenerator
{
	public :
		ParticleGravity(Vector3f gravity);

	void UpdateForce(std::shared_ptr<Particle> particle, float duration) override;

	private :
		Vector3f m_gravity;
};

