#include "include/ParticleStick.h"
#include "include/ParticuleCollision.h"

ParticleStick::ParticleStick(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float length) :
	ParticleLink(particle1, particle2),
	m_maxLength(length)
{
}

bool ParticleStick::CheckStretch(ParticleStick stick, std::tuple<Vector3f, float>* result)
{
	if (stick.GetLength() > stick.GetMaxLength())
	{
		*result = { (stick.m_linkedParticles[1]->GetPosition() - stick.m_linkedParticles[0]->GetPosition()).Normalize(), stick.GetDistance() };
		return true;
	}

	if (stick.GetLength() > stick.GetMaxLength())
	{
		*result = { -(stick.m_linkedParticles[1]->GetPosition() - stick.m_linkedParticles[0]->GetPosition()).Normalize(),  stick.GetDistance() };
		return true;
	}
	
	return false;
}

void ParticleStick::ResolveStretch(ParticleStick stick, float restitution, float distance, Vector3f normal)
{
	ParticuleCollision collision(stick.m_linkedParticles[0], stick.m_linkedParticles[1], restitution, distance, normal);
	collision.ApplyCollision();
}

float ParticleStick::GetDistance() const
{
	return GetLength() - GetMaxLength();
}

float ParticleStick::GetMaxLength() const
{
	return m_maxLength;
}
