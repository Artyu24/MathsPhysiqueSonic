#include "Particle.h"

Particle::Particle(Vector3<float> position, Vector3<float> velocity, float size, float mass) :
	m_position(position),
	m_velocity(velocity),
	m_size(size),
	m_invMass(mass)
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

Vector3<float> Particle::GetPrevPosition()
{
	return m_prevPosition;
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

void Particle::SetPrevPosition(const Vector3<float> value)
{
	m_prevPosition = value;
}

void Particle::SetSize(const float value)
{
	m_size = value;
}

void Particle::integrateurEuler(float deltaTime) {
	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;
	m_acceleration = Vector3<float> (0, 0, 0);
}

void Particle::integrateurVerlet(float deltaTime) {
	Vector3<float> newPosition = m_position * 2 - m_prevPosition + m_acceleration * deltaTime * deltaTime;
	m_prevPosition = m_position;
	m_position = newPosition;
	m_acceleration = Vector3<float> (0, 0, 0);
}