#include "include/World.h"

#include "include/ParticleGravity.h"
#include "include/ParticleFrictionCinetique.h"
#include "include/ParticleFrictionStatic.h"
#include "include/ParticleSpring.h"
#include "include/ParticleSpringFixedPoint.h"
#include "include/SphereCollider.h"

World::World() : m_particles(), m_forceRegistry(std::make_unique<ParticleForceRegistry>())
{
}

Vector3f World::m_gravity = Vector3f(0.0, 9.81f, 0.0f);

std::shared_ptr<Particle>  World::SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode)
{
	Particle particle(pos, data.initialVelocity, data.mass, 0.05f, isIntegrateEulerMode);
	std::shared_ptr<Particle> particleShared = std::make_shared<Particle>(particle);

	//Add Gravity
	ParticleGravity gravity(Vector3f(0, 9.8f, 0));
	std::shared_ptr<ParticleGravity> forceGeneratorGravity = std::make_shared<ParticleGravity>(gravity);
	m_forceRegistry->Add(particleShared, forceGeneratorGravity, GRAVITY);

	//Cinetique Force Test

	/*std::shared_ptr<ParticleFrictionCinetique> forceGeneratorShared = std::make_shared<ParticleFrictionCinetique>(particle.GetAcceleration() + m_gravity);
	m_forceRegistry->Add(particleShared, forceGeneratorShared);*/

	m_collisionSystem.AddCollider(particle.GetSize(), particleShared);
	m_particles.push_back(particleShared);

	return particleShared;
}

void World::SpawnBlob()
{
	for(int i = 0; i < 7; i++)
	{
		std::shared_ptr<Particle> particleShared = SpawnParticle({ Vector3f(0.f, 0.f, 0.f), 2 }, Vector3f(200.f + i * 20.f, 200.f + i * 20.f, 0.f));

		if(i == 0)
			continue;

		std::shared_ptr<ParticleSpring> forceGeneratorSharedSpring = std::make_shared<ParticleSpring>(m_particles[0], 5.f, 0.5f, 5.f, false);
		m_forceRegistry->Add(particleShared, forceGeneratorSharedSpring, SPRING_PARTICULE);
	}
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

void World::ApplyCollisions()
{
	m_collisionSystem.ApplyCollisions();
}

Vector3f World::GetGravity()
{
	return m_gravity;
}

void World::SetGravity(Vector3f gravity)
{
	m_gravity = gravity;
}


