#include "include/ParticleGravity.h"
#include "include/Particle.h"
#include "include/World.h"

ParticleGravity::ParticleGravity(Vector3f gravity) : m_gravity(gravity)
{
	World::SetGravity(m_gravity);
}

void ParticleGravity::UpdateForce(std::shared_ptr<Particle> particle, float duration)
{
	if(particle->GetInverseMass() != 0)
		particle->AddForce(m_gravity);
}
