#include "include/World.h"

#include "include/ParticleGravity.h"
#include "include/ParticleFrictionCinetique.h"
#include "include/ParticleFrictionStatic.h"

World::World() : m_particles(), m_forceRegistry(std::make_unique<ParticleForceRegistry>())
{
}

Vector3f World::m_gravity = Vector3f(0.0, 9.81f, 0.0f);

void World::SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode)
{
	Particle particle(pos, data.initialVelocity, data.mass, 0.05f, isIntegrateEulerMode);
	std::shared_ptr<Particle> particleShared = std::make_shared<Particle>(particle);
	m_particles.push_back(particleShared);

	//TEMP
	ParticleGravity gravity(Vector3f(0, 9.8f, 0));

		//Gravity Force Test
	//std::shared_ptr<ParticleGravity> forceGeneratorShared = std::make_shared<ParticleGravity>(gravity);
	//m_forceRegistry->Add(particleShared, forceGeneratorShared);

		//Static Force Test
	/*std::shared_ptr<ParticleFrictionStatic> forceGeneratorShared = std::make_shared<ParticleFrictionStatic>(10.0f);
	m_forceRegistry->Add(particleShared, forceGeneratorShared);*/

		//Cinetique Force Test
	std::shared_ptr<ParticleFrictionCinetique> forceGeneratorShared = std::make_shared<ParticleFrictionCinetique>(particle.GetAcceleration() + m_gravity);
	m_forceRegistry->Add(particleShared, forceGeneratorShared);
}

void World::UpdatePhysics(float duration)
{
	m_forceRegistry->UpdateForces(duration);

	for (auto& particule : m_particles)
	{
		particule->Integrate(duration);
	}
}

void World::Draw()
{
	//Draw Particle
	for (auto& particle : m_particles)
	{
		if (particle->GetIsIntegrateEuler())
			ofSetColor(255, 120, 120);
		else
			ofSetColor(120, 219, 255);

		ofDrawCircle(particle->GetPosition(), particle->GetSize());
	}
}

Vector3f World::GetGravity()
{
	return m_gravity;
}

void World::SetGravity(Vector3f gravity)
{
	m_gravity = gravity;
}


