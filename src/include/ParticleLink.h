#pragma once

#include "Particle.h"

class ParticleLink
{
	protected:
		std::array<std::shared_ptr<Particle>, 2> m_linkedParticles;

	public:
		ParticleLink(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2);

		float GetLength() const;
};

