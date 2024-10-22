#include "include/ParticuleCollision.h"
#include <cmath>

ParticuleCollision::ParticuleCollision(std::shared_ptr<Particle> particle1, float restitution, float overlap) :
m_restitution(restitution),
m_overlap(overlap),
m_collisionNormal(Vector3f{0.f, 1.0f, 0.0f})
{
	m_particles[0] = particle1;
	m_particles[1] = nullptr;
}

ParticuleCollision::ParticuleCollision(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float restitution, float overlap) :
	m_restitution(restitution),
	m_overlap(overlap)
{
	m_particles[0] = particle1;
	m_particles[1] = particle2;

	m_collisionNormal = (m_particles[1]->GetPosition() - m_particles[0]->GetPosition()).Normalize();
}

float ParticuleCollision::GetRestitution() const
{
	return m_restitution;
}

float ParticuleCollision::GetOverlap() const
{
	return m_overlap;
}

Vector3f ParticuleCollision::GetNormal() const
{
	return m_collisionNormal;
}

std::array<std::shared_ptr<Particle>, 2> ParticuleCollision::GetParticles() const
{
	return m_particles;
}

void ParticuleCollision::ApplyCollision()
{
	InternalResolveOverlap();
	InternalResolveImpulse();
}

float ParticuleCollision::CalculateRelativeVelocity()
{
	Vector3f totalVel = m_particles[0]->GetVelocity();
	if (m_particles[1])
		totalVel -= m_particles[1]->GetVelocity();

	return totalVel.DotProduct(m_collisionNormal);
}

float ParticuleCollision::InternalSumInvMass() const
{
	float sumInvMass = m_particles[0]->GetInverseMass();
	if (m_particles[1])
		sumInvMass += m_particles[1]->GetInverseMass();

	return sumInvMass;
}

void ParticuleCollision::InternalResolveImpulse()
{
	float relativeVelocity = CalculateRelativeVelocity();
	float e = m_restitution;
	float k = (e + 1) * relativeVelocity;

	float sumInvMass = InternalSumInvMass();

	k = k / sumInvMass;

	m_particles[0]->SetVelocity(m_particles[0]->GetVelocity() - m_collisionNormal * m_particles[0]->GetInverseMass() * k);

	if (m_particles[1])
		m_particles[1]->SetVelocity(m_particles[1]->GetVelocity() + m_collisionNormal * m_particles[1]->GetInverseMass() * k);
}

void ParticuleCollision::InternalResolveOverlap()
{
	if (m_overlap < 0)
		return;

	float sumInvMass = InternalSumInvMass();

	m_particles[0]->SetPosition(m_particles[0]->GetPosition() + m_collisionNormal * (1.f / m_particles[0]->GetInverseMass()) * sumInvMass * m_overlap);

	if (m_particles[1])
		m_particles[1]->SetPosition(m_particles[1]->GetPosition() + m_collisionNormal * (-1.f / m_particles[1]->GetInverseMass()) * sumInvMass * m_overlap);
}