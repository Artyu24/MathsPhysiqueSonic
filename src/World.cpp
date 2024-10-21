#include "include/World.h"

#include "include/ParticleGravity.h"
#include "include/ParticleFrictionCinetique.h"
#include "include/ParticleFrictionStatic.h"
#include "include/ParticleSpring.h"
#include "include/ParticleSpringFixedPoint.h"

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
	std::shared_ptr<ParticleGravity> forceGeneratorShared = std::make_shared<ParticleGravity>(gravity);
	m_forceRegistry->Add(particleShared, forceGeneratorShared, GRAVITY);

		//Static Force Test
	/*std::shared_ptr<ParticleFrictionStatic> forceGeneratorShared = std::make_shared<ParticleFrictionStatic>(10.0f);
	m_forceRegistry->Add(particleShared, forceGeneratorShared);*/

		//Cinetique Force Test

	/*std::shared_ptr<ParticleFrictionCinetique> forceGeneratorShared = std::make_shared<ParticleFrictionCinetique>(particle.GetAcceleration() + m_gravity);
	m_forceRegistry->Add(particleShared, forceGeneratorShared);*/

	//m_forceRegistry->Remove(particleShared, GRAVITY);

	//std::shared_ptr<ParticleFrictionCinetique> forceGeneratorShared = std::make_shared<ParticleFrictionCinetique>(particle.GetAcceleration() + m_gravity);
	//m_forceRegistry->Add(particleShared, forceGeneratorShared);

		//Spring
	/*std::shared_ptr<ParticleSpringFixedPoint> forceGeneratorShared = std::make_shared<ParticleSpringFixedPoint>(Vector3f(500.f,300.f,0.f), 5.f, 0.5f, 5.f, true);
	m_forceRegistry->Add(particleShared, forceGeneratorShared);*/

	//SpringParticle

	Vector3f anchorPosition(500.f, 500.f, 0.f);  
	Vector3f anchorVelocity(0, 0, 0);
	float anchorMass = 1.0f;  
	bool anchorIsEulerMode = true;  

	Particle anchor(anchorPosition, anchorVelocity, anchorMass, 0.05f, anchorIsEulerMode);
	std::shared_ptr<Particle> anchorParticle = std::make_shared<Particle>(anchor);
	m_particles.push_back(anchorParticle);

	std::shared_ptr<ParticleSpring> forceGeneratorShared = std::make_shared<ParticleSpring>(anchorParticle.get(), 5.f, 0.5f, 5.f, false);
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


