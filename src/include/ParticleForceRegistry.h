#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
public:
	struct ParticleForceRegistration
	{
		ParticleForceRegistration(Particle* p, IParticleForceGenerator* fg) : particle(p), forceGenerator(fg){};
		Particle* particle;
		IParticleForceGenerator* forceGenerator;
	};


	void Add(Particle* particle, IParticleForceGenerator* fG);
	void Remove(Particle* particle, IParticleForceGenerator* fG);
	void Clear() const;

	void UpdateForces(float duration);

private :
	std::vector<ParticleForceRegistration> m_registre;
};

