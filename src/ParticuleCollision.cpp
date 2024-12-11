#include "include/ParticuleCollision.h"
#include <cmath>

ParticuleCollision::ParticuleCollision(std::shared_ptr<Particle> particle1, float restitution, float overlap, Vector3f normal) :
    m_restitution(restitution),
    m_overlap(overlap),
    m_collisionNormal(normal) 
{
    m_particles[0] = particle1;
    m_particles[1] = nullptr;
}

ParticuleCollision::ParticuleCollision(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float restitution, float overlap, Vector3f normal) :
	m_restitution(restitution),
	m_overlap(overlap),
	m_collisionNormal(normal)
{
	m_particles[0] = particle1;
	m_particles[1] = particle2;
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

    //std::cout << totalVel.DotProduct(m_collisionNormal)<< std::endl;

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
	float relativeVelocity = CalculateRelativeVelocity() ;
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
    // Clamp l'overlap pour éviter les valeurs trop grandes ou négatives
    m_overlap = std::clamp(m_overlap, 0.0f, 5.0f);

    float sumInvMass = InternalSumInvMass();
    float correctionFactor = 0.05f;
    float overlapCorrection = m_overlap * correctionFactor;

    Vector3f minimalCorrection = m_collisionNormal * 0.05f;

    if (m_particles[0]->GetIsPlane()) {
        m_particles[1]->SetPosition(
            m_particles[1]->GetPosition() + minimalCorrection + m_collisionNormal * (-1.f / m_particles[1]->GetInverseMass()) * overlapCorrection
        );
        return;
    }

    if (m_particles[1] && m_particles[1]->GetIsPlane()) {
        m_particles[0]->SetPosition(
            m_particles[0]->GetPosition() + minimalCorrection + m_collisionNormal * (1.f / m_particles[0]->GetInverseMass()) * overlapCorrection
        );
        return;
    }

    m_particles[0]->SetPosition(
        m_particles[0]->GetPosition() + minimalCorrection + m_collisionNormal * (1.f / m_particles[0]->GetInverseMass()) * overlapCorrection
    );

    if (m_particles[1]) {
        m_particles[1]->SetPosition(
            m_particles[1]->GetPosition() + minimalCorrection + m_collisionNormal * (-1.f / m_particles[1]->GetInverseMass()) * overlapCorrection
        );
    }

    Vector3f velocity = m_particles[0]->GetVelocity();
    m_particles[0]->SetVelocity(velocity * 0.5f);

    if (m_particles[1]) {
        velocity = m_particles[1]->GetVelocity();
        m_particles[1]->SetVelocity(velocity * 0.5f);
    }
}