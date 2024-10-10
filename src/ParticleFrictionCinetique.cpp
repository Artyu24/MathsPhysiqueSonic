#include "include/ParticleFrictionCinetique.h"
#include "include/Particle.h"

ParticleFrictionCinetique::ParticleFrictionCinetique(Vector3f acceleration) : m_acceleration(acceleration)
{
}

void ParticleFrictionCinetique::UpdateForce(std::shared_ptr<Particle> particle, float duration)
{
	particle->AddForce(m_acceleration * (1.0 / particle->GetInverseMass()));
}
