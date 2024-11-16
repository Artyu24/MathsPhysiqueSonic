#include "include/World.h"

#include "include/ParticleGravity.h"
#include "include/ParticleFrictionCinetique.h"
#include "include/ParticleFrictionStatic.h"
#include "include/ParticleSpring.h"
#include "include/ParticleSpringFixedPoint.h"
#include "include/SphereCollider.h"

World::World() :
m_particles(),
m_forceRegistry(std::make_unique<ParticleForceRegistry>()) //Create Force Registry
{
}

void World::LaunchGame()
{
	
}

void World::SpacePressed()
{
	
}

void World::Movement(Vector3f force)
{
	m_firstBlobParticle->AddForce(force);
}

Vector3f World::m_gravity = Vector3f(0.0, -9.81f, 0.0f);

std::shared_ptr<Particle>  World::SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode)
{
	//Create Particle
	Particle particle(pos, data.initialVelocity, data.mass, 0.05f, isIntegrateEulerMode);
	std::shared_ptr<Particle> particleShared = std::make_shared<Particle>(particle);
	 
	//Add Gravity
	ParticleGravity gravity(m_gravity);
	std::shared_ptr<ParticleGravity> forceGeneratorGravity = std::make_shared<ParticleGravity>(gravity);
	m_forceRegistry->Add(particleShared, forceGeneratorGravity, GRAVITY);

	//Add Collider
	m_collisionSystem.AddCollider(particle.GetSize(), particleShared);

	//Add Particle to list
	m_particles.push_back(particleShared);

	return particleShared;
}

std::shared_ptr<RigidBody>  World::SpawnRigidBody(ParticleData data, Vector3f pos, float duration)
{
	std::shared_ptr<Particle> particleShared = SpawnParticle(data, pos);
	
	RigidBody rb(particleShared);
	std::shared_ptr<RigidBody> rigidBodyShared = std::make_shared<RigidBody>(rb);
	m_rigidBody.push_back(rigidBodyShared);

	return rigidBodyShared;
}

void World::UpdatePhysics(float duration)
{
	m_forceRegistry->UpdateForces(duration);
	
	for (auto& rb : m_rigidBody) 
	{
		rb->ApplyTorque({ 0.f,0.f, -100.f });
		rb->UpdateState(duration);
	}

	for (auto& particule : m_particles)
	{
		particule->Integrate(duration);
	}

	
}

void World::Draw()
{
	//Draw Particle
	for (auto& rb : m_rigidBody)
	{
		

		ofPushMatrix();

		ofTranslate(rb->GetPosition());

		
		
		glm::quat orientation = glm::quat(rb->GetOrientation().GetNormalize());
		glm::mat4 rotationMat = glm::toMat4(orientation);
		ofMultMatrix(rotationMat);



		ofNoFill();
		ofSetColor(255);
		ofDrawBox(0, 0, 0, 50);

		ofSetColor(255.f, 0.f, 0.f);
		ofDrawSphere(0, 0, 0, 5.f);

		ofPopMatrix();

	}


}

void World::ApplyCollisions()
{
	m_collisionSystem.ApplyCollisions();
}

void World::ApplyGroundCollisions()
{
	m_collisionSystem.ApplyGroundCollisions();
}

Vector3f World::GetGravity()
{
	return m_gravity;
}

void World::SetGravity(Vector3f gravity)
{
	m_gravity = gravity;
}
