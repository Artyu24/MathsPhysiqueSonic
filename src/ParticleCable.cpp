#include "include/ParticleCable.h"
#include "include/ParticuleCollision.h"

ParticleCable::ParticleCable(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float maxlength) :
    ParticleLink(particle1, particle2),
    m_maxlength(maxlength)
{
}

bool ParticleCable::CheckStretch(ParticleCable cable, std::tuple<Vector3f, float>* result)
{
    if (cable.GetLength() >= cable.GetMaxLength())
    {
        *result = { (cable.m_linkedParticles[1]->GetPosition() - cable.m_linkedParticles[0]->GetPosition()).Normalize(), cable.GetLength() - cable.GetMaxLength() };
    }
    return false;
}

void ParticleCable::ResolveStretch(ParticleCable cable, float restitution, float distance, Vector3f normal)
{
    ParticuleCollision collision(cable.m_linkedParticles[0], cable.m_linkedParticles[1], restitution, distance, normal);
    collision.ApplyCollision();
}

float ParticleCable::GetMaxLength() const
{
    return m_maxlength;
}
