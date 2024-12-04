#include "include/Particle.h"

Particle::Particle(Vector3f pos) :
	m_position(pos)
{

}

Particle::Particle(Vector3f position, Vector3f velocity, float mass, float damping, bool isIntegrateEuler) :
	m_position(position),
	m_velocity(velocity),
	m_acceleration(),
	m_prevPosition(position),
	m_invMass(1.f / mass),
	m_size(mass / 50),
	m_damping(damping),
	m_isIntegrateEuler(isIntegrateEuler)
{

	//We integrate Euler at start to get a first previous position needed for integrate Verlet
	if (!m_isIntegrateEuler) {
		m_prevPosition = m_position;
		Vector3f gravity(0, 9.8f, 0);
		this->AddForce(gravity);
		IntegrateEuler(0.033f * 10.f); //We set the deltaTime to get the same start for every Particle
	}
}

Vector3f Particle::GetPosition() const
{
	return m_position;
}

Vector3f Particle::GetVelocity() const
{
	return m_velocity;
}

Vector3f Particle::GetAcceleration() const
{
	return m_acceleration;
}

Vector3f Particle::GetPrevPosition() const
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

float Particle::GetDamping() const
{
	return m_damping;
}

bool Particle::GetIsIntegrateEuler() const
{
	return m_isIntegrateEuler;
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

void Particle::AddForceGeneratorToMap(ForceEnum forceEnum, std::shared_ptr<IParticleForceGenerator> fG)
{
	auto it = m_forceMap.find(forceEnum);
	if (it != m_forceMap.end())
		return;

	m_forceMap.emplace(forceEnum, fG);
}

std::shared_ptr<IParticleForceGenerator> Particle::GetForceGenerator(ForceEnum forceEnum)
{
	auto it = m_forceMap.find(forceEnum);
	if (it != m_forceMap.end())
		return it->second;

	return nullptr;
}

void Particle::RemoveForceGeneratorToMap(ForceEnum forceEnum)
{
	auto it = m_forceMap.find(forceEnum);
	if (it != m_forceMap.end())
		m_forceMap.erase(it);
}

void Particle::RemoveAllForceGeneratorToMap()
{
	m_forceMap.clear();
}

// Apply a force to the particle
void Particle::AddForce(Vector3f force)
{
	Vector3f accel = force + m_velocity * m_invMass - (m_velocity * (1 - m_damping)) * m_invMass;  // F = m * a -> a = F / m
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
	m_position += m_velocity * deltaTime + m_acceleration * 0.5f * pow(deltaTime, 2);
	m_acceleration = Vector3f (0, 0, 0);
}

void Particle::IntegrateVerlet(float deltaTime)
{
	Vector3f newPosition = m_position * 2 - m_prevPosition + m_acceleration * pow(deltaTime, 2);
	m_velocity += m_acceleration  * deltaTime;
	m_prevPosition = m_position;
	m_position = newPosition;
	m_acceleration = Vector3f(0, 0, 0);
}