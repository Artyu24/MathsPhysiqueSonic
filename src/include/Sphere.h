#pragma once

#include <memory>

class Particle;

class Sphere : public std::enable_shared_from_this<Sphere>
{
	public:
		explicit Sphere(std::shared_ptr<Particle> particle, float radius);

		float GetRadius() const;
		std::shared_ptr<Particle> GetParticle() const;

		const bool IsColliding(std::shared_ptr<Sphere>& otherSphere);
		static const bool IsCollidingStatic(std::shared_ptr<Sphere>& first, std::shared_ptr<Sphere>& second);

	private:
		float m_radius;
		std::shared_ptr<Particle> m_particle;
};

