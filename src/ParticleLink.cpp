#include "include/ParticleLink.h"

ParticleLink::ParticleLink(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2)
{
	m_linkedParticles[0] = particle1;
	m_linkedParticles[1] = particle2;
}

float ParticleLink::GetLength() const
{
	return (m_linkedParticles[1]->GetPosition() - m_linkedParticles[0]->GetPosition()).Length();
}
