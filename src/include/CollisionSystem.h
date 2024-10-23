#pragma once

#include <vector>
#include "SphereCollider.h"
#include "Particle.h"
#include "ParticleCable.h"
#include "ParticleStick.h"

constexpr float e = 1.f;
constexpr float yFloor = 600.f;

class CollisionSystem
{
	public:
		void ApplyCollisions();
		void ApplyGroundCollisions();
		void ApplyCableCollisions();
		void ApplyStickCollisions();

		void AddCollider(float r, std::shared_ptr<Particle> particle);
		void AddCable(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float cableLength);
		void AddStick(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float sticklength);

		std::vector<SphereCollider>& GetAllColliders() { return m_colliders;}
	private:
		std::vector<ParticleCable> m_cables;
		std::vector<ParticleStick> m_sticks;
		std::vector<SphereCollider> m_colliders;
		std::unordered_map<SphereCollider*, CollisionCallback> m_callbacksToCall;
};

