#pragma once

#include <memory>

class Particle;

class Sphere
{
	public:
		explicit Sphere(std::shared_ptr<Particle> particle, float radius);

		float GetRadius() const;
		std::shared_ptr<Particle> GetParticle() const;

		const bool IsColliding(const Sphere& otherSphere);
		static const bool IsCollidingStatic(const Sphere& first, const Sphere& second);

		void SetRadius(float radius);
		
	private:
		float m_radius;
		std::shared_ptr<Particle> m_particle;
};

