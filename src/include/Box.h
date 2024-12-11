#pragma once

#include <memory>
#include <functional>
#include <array>

class Particle;
class RigidBody;
struct CollisionCallback;

template<typename T> struct Vector3;
using Vector3f = Vector3<float>;

class Box
{
	public:
		explicit Box(std::shared_ptr<Particle> particle, float size, float restitution = 1.0f);

		float GetSize() const;
		float GetRestitution() const;
		Vector3f GetCenter() const;
		std::shared_ptr<Particle> GetParticle() const;

		std::array<Vector3f, 8> GetBoxVertices(const RigidBody &rb) const;

		void SetSize(float size);

	private:
		std::shared_ptr<Particle> m_particle;
		/*std::shared_ptr<RigidBody> m_rigidbody;*/
		float m_size;
		float m_restitution;
		std::function<void(CollisionCallback)> m_delegates;
};

