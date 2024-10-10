#pragma once
#include "ParticleForceGenerator.h"


class ParticleFrictionCinetique : public IParticleForceGenerator
{
public:
	ParticleFrictionCinetique(Vector3f acceleration);

	void UpdateForce(std::shared_ptr<Particle> particle, float duration) override;

private :
	Vector3f m_acceleration;
};

