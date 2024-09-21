#include "include/Particle.h"

Particle::Particle(Vector3f position, Vector3f velocity, float mass, bool isIntegrateEuler) :
	m_position(position),
	m_velocity(velocity),
	m_acceleration(),
	m_prevPosition(position),
	m_invMass(1.f / mass),
	m_size(mass * 0.5f),
	m_isIntegrateEuler(isIntegrateEuler)
{

	//We integrate Euler at start to get a first previous position needed for integrate Verlet
	if(!m_isIntegrateEuler)
		IntegrateEuler(0.033f); //We set the deltaTime to get the same start for every Particle
}


Vector3f Particle::GetPosition()
{
	return m_position;
}

Vector3f Particle::GetVelocity()
{
	return m_velocity;
}

Vector3f Particle::GetAcceleration()
{
	return m_acceleration;
}

Vector3f Particle::GetPrevPosition()
{
	return m_prevPosition;
}

float Particle::GetSize() const
{
	return m_size;
}

float Particle::GetInverseMass() const
{
	return m_invMass;
}

void Particle::SetPosition(const Vector3f value)
{
	m_position = value;
}

void Particle::SetVelocity(const Vector3f value)
{
	m_velocity = value;
}

void Particle::SetAcceleration(const Vector3f value)
{
	m_acceleration = value;
}

void Particle::SetPrevPosition(const Vector3f value)
{
	m_prevPosition = value;
}

void Particle::SetSize(const float value)
{
	m_size = value;
}

// Apply a force to the particle
void Particle::ApplyForce(Vector3f force)
{
	Vector3f accel = force / m_invMass;  // F = m * a -> a = F / m
	m_acceleration += accel;
}

void Particle::Integrate(float deltaTime)
{
	if (m_isIntegrateEuler)
		IntegrateEuler(deltaTime);
	else
		IntegrateVerlet(deltaTime);
}

void Particle::IntegrateEuler(float deltaTime)
{
	m_velocity += m_acceleration * deltaTime;
	m_position += m_velocity * deltaTime;
	m_acceleration = Vector3f (0, 0, 0);
}

void Particle::IntegrateVerlet(float deltaTime)
{
	Vector3f newPosition = m_position * 2 - m_prevPosition + m_acceleration * pow(deltaTime, 2);
	m_prevPosition = m_position;
	m_position = newPosition;
	m_acceleration = Vector3f(0, 0, 0);
}

