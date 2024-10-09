#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
public:
	struct ParticleForceRegistration
	{
		ParticleForceRegistration(std::shared_ptr<Particle> p, std::shared_ptr<IParticleForceGenerator> fg) : particle(p), forceGenerator(fg){};
		std::shared_ptr<Particle> particle;
		std::shared_ptr<IParticleForceGenerator> forceGenerator;
	};


	void Add(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForceGenerator> fG);
	void Remove(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForceGenerator> fG);
	void Clear() const;

	void UpdateForces(float duration);

private :
	std::vector<std::unique_ptr<ParticleForceRegistration>> m_registre;
};

