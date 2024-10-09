#include "include/World.h"

#include "include/ParticleGravity.h"

World::World() : m_particles(), m_forceRegistry(std::make_unique<ParticleForceRegistry>())
{
}

void World::SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode)
{
	Particle particle(pos, data.initialVelocity, data.mass, 0.05f, isIntegrateEulerMode);
	std::shared_ptr<Particle> particleShared = std::make_shared<Particle>(particle);
	m_particles.push_back(particleShared);

	//TEMP
	ParticleGravity gravity(Vector3f(0, 9.8f, 0));
	std::shared_ptr<ParticleGravity> forceGeneratorShared = std::make_shared<ParticleGravity>(gravity);
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
