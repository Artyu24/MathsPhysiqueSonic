#pragma once

#include <tuple>
#include <vector>
#include <functional>
#include "Particle.h"

template<typename T> struct Vector3;
using Vector3f = Vector3<float>;
class SphereCollider;

struct CollisionCallback
{
	SphereCollider* collider;
};

class SphereCollider
{
	public:
		SphereCollider(float r, std::shared_ptr<Particle> particle, bool enabled = true);

		float GetRadius() const;
		void SetRadius(float radius);
		bool IsEnabled() const;

		void AddCollisionFunction(std::function<void(CollisionCallback)> func);
		void ColliderCallBack(CollisionCallback callback) const;

		inline void Enable() { m_isEnabled = true; };
		inline void Disable() {	m_isEnabled = false; };

		static bool CheckCollision(SphereCollider& col1, SphereCollider& col2, std::tuple<Vector3f, double>* result);
		static bool CheckCollisionGround(SphereCollider& col1, float groundY, std::tuple<Vector3f, double>* result);

		static void ResolveCollision(SphereCollider& col1, SphereCollider& col2, float restitution, std::tuple<Vector3f, double> info);
		static void ResolveCollision(SphereCollider& col1, float restitution, std::tuple<Vector3f, double> info);

		std::shared_ptr<Particle> GetParticle() const;
	
	private:
		float m_radius;
		bool m_isEnabled;
		std::shared_ptr<Particle> m_particle;
		std::vector<std::function<void(CollisionCallback)>> m_delegates;
};

