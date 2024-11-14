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
	SpawnBlob();
}

void World::SpacePressed()
{
	DivideBlob();
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
		rb->UpdateState(duration);
	}

	for (auto& particule : m_particles)
	{
		particule->Integrate(duration);
	}

	if (m_firstBlobParticle->GetVelocity().Length() >= 25.f) //Limite la vitesse
	{
		if (m_firstBlobParticle->GetVelocity().x > 0.f)
		{
			m_firstBlobParticle->SetVelocity({ 25.f,0.f,0.f });
		}
		else if (m_firstBlobParticle->GetVelocity().x < 0.f)
		{
			m_firstBlobParticle->SetVelocity({ -25.f,0.f,0.f });
		}

	}
}

void World::Draw()
{
	//Draw Particle
	for (auto& rb : m_rigidBody)
	{
		/*if(particle == m_firstBlobParticle)
		{
			ofSetColor(41, 227, 177);
			ofDrawCircle(particle->GetPosition(), particle->GetSize() * (m_particleInsideBlob + 1));
		}
		else
		{
			ofSetColor(51, 161, 79);
			ofDrawCircle(particle->GetPosition(), particle->GetSize());
		}*/

		ofNoFill();
		ofSetColor(255);
		ofDrawBox(rb->GetPosition(), 100);

		ofSetColor(255.f, 0., 0.);
		ofDrawSphere(rb->GetPosition(), 10.f);

	}

	ofDrawBitmapString("Nb Particles : " + ofToString(m_particleInsideBlob), ofGetWidth() - 220.f, 60.f);
	ofDrawBitmapString("Nb Attached Particles : " + ofToString((m_particleInsideBlob - 7)*( - 1)), ofGetWidth() - 220.f, 90.f);

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

//Temp For Game
void World::SpawnBlob()
{
	//Spawn First Particle
	std::shared_ptr<Particle> particleShared = SpawnParticle(m_defaultParticleData, Vector3f(200.f, 570.f, 0.f));
	m_firstBlobParticle = particleShared;

	m_collisionSystem.GetAllColliders()[0].AddCollisionFunction([&](CollisionCallback callback) 
		{ 
			GatherBlobParticle(callback.collider->GetParticle());

			auto it = std::find_if(m_collisionSystem.GetAllColliders().begin(), m_collisionSystem.GetAllColliders().end(), [callback](const SphereCollider c) -> bool { return c.GetParticle() == callback.collider->GetParticle(); });
			m_collisionSystem.GetAllColliders().erase(it);
		});
}

void World::DivideBlob()
{
	for (int i = 0; i < m_particleInsideBlob; i++)
	{
		std::shared_ptr<Particle> particleShared = SpawnParticle(m_defaultParticleData, m_firstBlobParticle->GetPosition() + Vector3f(20.f + (i + 1) * 20.f, 0.f, 0.f));

		//Create Spring Force for every divided particle with the main blob particle
		std::shared_ptr<ParticleSpring> forceGeneratorSharedSpring = std::make_shared<ParticleSpring>(m_firstBlobParticle, 50.f, 0.1f, 100.f, false);
		m_forceRegistry->Add(particleShared, forceGeneratorSharedSpring, SPRING_PARTICULE);
	}

	m_particleInsideBlob = 0;
}

void World::GatherBlobParticle(std::shared_ptr<Particle> particle)
{
	if (particle == nullptr)
		return;

	auto it = std::find(m_particles.begin(), m_particles.end(), particle);
	if (it == m_particles.end())
		return;

	m_forceRegistry->RemoveAll(particle);
	(particle)->RemoveAllForceGeneratorToMap();
	m_particles.erase(it);

	m_particleInsideBlob++;
	m_collisionSystem.GetAllColliders()[0].SetRadius(m_particles[0]->GetSize() * (m_particleInsideBlob + 1));
}
