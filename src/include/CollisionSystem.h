#pragma once

#include <vector>
#include "SphereCollider.h"
#include "Particle.h"

constexpr float e = 1.f;
constexpr float yFloor = 600.f;

class CollisionSystem
{
	public:
		void ApplyCollisions();
		void AddCollider(float r, std::shared_ptr<Particle> particle);

	private:
		std::vector<SphereCollider> m_colliders;
		std::unordered_map<SphereCollider*, Particle*> m_callbacksToCall;
};

