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
		void ApplyGroundCollisions();
		void AddCollider(float r, std::shared_ptr<Particle> particle);
		//void AddCable();

		std::vector<SphereCollider>& GetAllColliders() { return m_colliders;}
	private:
		std::vector<SphereCollider> m_colliders;
		std::vector<SphereCollider> m_groundSensors;
		std::unordered_map<SphereCollider*, std::shared_ptr<Particle>> m_callbacksToCall;
};

