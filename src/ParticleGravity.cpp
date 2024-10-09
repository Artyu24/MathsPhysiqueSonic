#include "include/ParticleGravity.h"
#include "include/Particle.h"

ParticleGravity::ParticleGravity(Vector3f gravity) : m_gravity(gravity)
{
}

void ParticleGravity::UpdateForce(std::shared_ptr<Particle> particle, float duration)
{
	particle->AddForce(m_gravity);
}
