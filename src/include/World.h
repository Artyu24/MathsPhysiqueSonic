#pragma once

#include "ParticleData.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "CollisionSystem.h"

class World
{
public:
	World();

	//Game
	void LaunchGame();

	//Game Temp
	void SpacePressed();
	void Movement(Vector3f force);

	std::shared_ptr<Particle> SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode = true);

	//Physics
	void UpdatePhysics(float duration);
	void ApplyCollisions();
	void ApplyGroundCollisions();

	//Draw
	void Draw();

	static Vector3f GetGravity();
	static void SetGravity(Vector3f gravity);

private:
	std::vector<std::shared_ptr<Particle>> m_particles;
	std::unique_ptr<ParticleForceRegistry> m_forceRegistry;

	CollisionSystem m_collisionSystem;

	static Vector3f m_gravity;

	//Game Temp
	int m_particleInsideBlob = 7;
	ParticleData m_defaultParticleData = { Vector3f(0.f,0.f,0.f), 200 };
	std::shared_ptr<Particle> m_firstBlobParticle;

	

	void SpawnBlob();
	void DivideBlob();
	void GatherBlobParticle(std::shared_ptr<Particle> particle);

};
