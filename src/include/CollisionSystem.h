#pragma once

#include <vector>
#include <tuple>
#include <array>
#include "SphereCollider.h"
#include "Particle.h"
#include "ParticleCable.h"
#include "ParticleStick.h"
#include "Vector3.h"


class Plane;
class Box;
struct CollisionCallback3D;

constexpr float e = 1.f;
constexpr float yFloor = 600.f;

const std::array<Vector3f, 6> faces
{
	Vector3f{1.f, 0.f, 0.f},
	Vector3f{0.f, 1.f, 0.f},
	Vector3f{0.f, 0.f, 1.f},
	Vector3f{-1.f, 0.f, 0.f},
	Vector3f{0.f, -1.f, 0.f},
	Vector3f{0.f, 0.f, -1.f}
};

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

		bool CheckCollisionBox(const Box& box1, const Box& box2, CollisionCallback3D& callback);

		/** result:
			float -> interpenetration
			Vector3f -> Point d'impact
			Vector3f -> face traversee
		*/
		bool CheckVertexInsideBox(const Box& box, Vector3f vertex, std::tuple<float, Vector3f, Vector3f>& result);

		std::vector<SphereCollider>& GetAllColliders() { return m_colliders;}

	private:
		std::vector<ParticleCable> m_cables;
		std::vector<ParticleStick> m_sticks;
		std::vector<SphereCollider> m_colliders;
		std::unordered_map<SphereCollider*, CollisionCallback> m_callbacksToCall;
};

