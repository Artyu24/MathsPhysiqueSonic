#include "include/ParticleForceRegistry.h"

void ParticleForceRegistry::Add(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForceGenerator> fG, ForceEnum forceEnum)
{
    particle->AddForceGeneratorToMap(forceEnum, fG);
    ParticleForceRegistration pFR(particle, fG);
	m_registre.push_back(std::make_unique<ParticleForceRegistration>(pFR));
}

void ParticleForceRegistry::Remove(std::shared_ptr<Particle> particle, ForceEnum forceEnum)
{
    for(auto it = m_registre.begin(); it != m_registre.end(); it++)
    {
	    if((*it)->particle == particle)
	    {
            if(particle->GetForceGenerator(forceEnum) != nullptr && particle->GetForceGenerator(forceEnum) == (*it)->forceGenerator)
            {
                particle->RemoveForceGeneratorToMap(forceEnum);
				m_registre.erase(it);
	            break;
            }
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
        particleFR->forceGenerator->UpdateForce(particleFR->particle, duration);
    }
}
