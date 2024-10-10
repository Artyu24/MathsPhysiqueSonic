#include "include/ParticleFrictionStatic.h"
#include "include/Particle.h"
#include "include/World.h"

ParticleFrictionStatic::ParticleFrictionStatic(float CoefStaticForce) : m_coefStaticForce(CoefStaticForce)
{
}

void ParticleFrictionStatic::UpdateForce(std::shared_ptr<Particle> particle, float duration)
{
	m_normalForce = World::GetGravity() * (1.0f / particle->GetInverseMass());

	if (World::GetGravity().Length() <= (m_normalForce * m_coefStaticForce).Length())
	{
		particle->SetVelocity(Vector3f(0.0f, 0.0f, 0.0f));
		
	}
	
}
