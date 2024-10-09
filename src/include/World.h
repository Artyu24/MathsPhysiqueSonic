#pragma once

#include "ParticleData.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"

class World
{
public:
	World();

	void SpawnParticle(ParticleData data, Vector3f pos, bool isIntegrateEulerMode);

	void UpdatePhysics(float duration);
	void Draw();

private:
	std::vector<std::shared_ptr<Particle>> m_particles;

	std::unique_ptr<ParticleForceRegistry> m_forceRegistry;
};
