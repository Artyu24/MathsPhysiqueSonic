#include "Particle.h"

Particle::Particle(Vector3<float> position, float size) : 
	m_position(position),
	m_size(m_size)
{
}


Vector3<float> Particle::GetPosition()
{
	return m_position;
}

Vector3<float> Particle::GetVelocity()
{
	return m_velocity;
}

Vector3<float> Particle::GetAcceleration()
{
	return m_acceleration;
}

float Particle::GetSize()
{
	return m_size;
}

float Particle::GetInverseMass()
{
	return m_invMass;
}

void Particle::SetPosition(const Vector3<float> value)
{
	m_position = value;
}

void Particle::SetVelocity(const Vector3<float> value)
{
	m_velocity = value;
}

void Particle::SetAcceleration(const Vector3<float> value)
{
	m_acceleration = value;
}

void Particle::SetSize(const float value)
{
	m_size = value;
}
