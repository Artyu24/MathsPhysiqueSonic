#pragma once
#include "ParticleForceGenerator.h"

class ParticleFrictionStatic : public IParticleForceGenerator
{

public:
	ParticleFrictionStatic(float CoefStaticForce);

	void UpdateForce(std::shared_ptr<Particle> particle, float duration) override;

private :
	float m_coefStaticForce;
	Vector3f m_normalForce; // m_normalForce = masse * gravity
};

