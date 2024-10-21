#pragma once

#include "ParticleData.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"
#include "CollisionSystem.h"

class World
{
public:
	World();

	std::shared_ptr<Particle> SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode = true);
	void SpawnBlob();

	void UpdatePhysics(float duration);
	void Draw();
	void ApplyCollisions();

	static Vector3f GetGravity();
	static void SetGravity(Vector3f gravity);

private:
	std::vector<std::shared_ptr<Particle>> m_particles;

	std::unique_ptr<ParticleForceRegistry> m_forceRegistry;

	CollisionSystem m_collisionSystem;

	static Vector3f m_gravity;
};
