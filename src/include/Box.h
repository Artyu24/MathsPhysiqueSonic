#pragma once

#include <memory>
#include <functional>
#include <array>

class Particle;
struct CollisionCallback;

template<typename T> struct Vector3;
using Vector3f = Vector3<float>;

class Box
{
	public:
		explicit Box(std::shared_ptr<Particle> particle, float size);

		float GetSize() const;
		Vector3f GetCenter() const;

		std::array<Vector3f, 8> GetBoxVertices() const;

	private:
		std::shared_ptr<Particle> m_particle;
		float m_size;
		std::function<void(CollisionCallback)> m_delegates;
};

