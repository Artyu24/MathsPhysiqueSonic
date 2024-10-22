#include "include/ParticleForceRegistry.h"

//Add Force to a Particle
void ParticleForceRegistry::Add(std::shared_ptr<Particle> particle, std::shared_ptr<IParticleForceGenerator> fG, ForceEnum forceEnum)
{
    particle->AddForceGeneratorToMap(forceEnum, fG);
    ParticleForceRegistration pFR(particle, fG);
	m_registre.push_back(std::make_unique<ParticleForceRegistration>(pFR));
}

//Remove Force to a Particle by Enum
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

void ParticleForceRegistry::RemoveAll(std::shared_ptr<Particle> particle)
{
    for (auto it = m_registre.begin(); it != m_registre.end(); it++)
    {
        if ((*it)->particle == particle)
        {
        	particle->RemoveAllForceGeneratorToMap();
            m_registre.erase(it);
            break;
        }
    }
}


//Clear all registry
void ParticleForceRegistry::Clear() const
{
    m_registre.empty();
}

//Update Every Forces for every Particle
void ParticleForceRegistry::UpdateForces(float duration)
{
    for (auto& particleFR : m_registre)
    {
        particleFR->forceGenerator->UpdateForce(particleFR->particle, duration);
    }
}
