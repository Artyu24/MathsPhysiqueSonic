#pragma once

#include <memory>
#include <functional>

class Particle;
struct CollisionCallback;

class Box
{
	public:
		explicit Box(std::shared_ptr<Particle> particle, float size);

		const bool IsColliding(const Box& otherBox, CollisionCallback& results);
		static const bool IsCollidingStatic(const Box& first, const Box& second, CollisionCallback& results);

	private:
		std::shared_ptr<Particle> m_particle;
		float m_size;
		std::function<void(CollisionCallback)> m_delegates;
};

