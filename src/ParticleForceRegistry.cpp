#include "include/ParticleForceRegistry.h"

void ParticleForceRegistry::Add(Particle* particle, IParticleForceGenerator* fG)
{
	m_registre.push_back({ particle, fG });
}

void ParticleForceRegistry::Remove(Particle* particle, IParticleForceGenerator* fG)
{
    for(auto it = m_registre.begin(); it != m_registre.end(); it++)
    {
	    if(it->particle == particle && it->forceGenerator == fG)
	    {
			m_registre.erase(it);
            break;
	    }
    }
}

void ParticleForceRegistry::Clear() const
{
    m_registre.empty();
}

void ParticleForceRegistry::UpdateForces(float duration)
{
    for (auto& particleFR : m_registre)
    {
        particleFR.forceGenerator->UpdateForce(particleFR.particle, duration);
    }
}
