#pragma once

#include "Particle.h"

class ParticuleCollision
{
	public:
		ParticuleCollision(std::shared_ptr<Particle> particle1, float restitution, float overlap);
		ParticuleCollision(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float restitution, float overlap, Vector3f normal);

		float GetRestitution() const;
		float GetOverlap() const;
		Vector3f GetNormal() const;
		std::array<std::shared_ptr<Particle>, 2> GetParticles() const;

		void ApplyCollision();
		float CalculateRelativeVelocity();

	private:
		std::array<std::shared_ptr<Particle>, 2> m_particles;
		float m_restitution;
		float m_overlap;
		Vector3f m_collisionNormal;

		float InternalSumInvMass() const;

		void InternalResolveImpulse();
		void InternalResolveOverlap();
};

