#pragma once

#include "ParticleLink.h"
#include <tuple>

class ParticleStick : public ParticleLink
{
	public:
		ParticleStick(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float length);

		static bool CheckStretch(ParticleStick stick, std::tuple<Vector3f, float>* result);
		static void ResolveStretch(ParticleStick stick, float restitution, float distance, Vector3f normal);

		float GetDistance() const;
		float GetMaxLength() const;

	private:
		float m_maxLength;

};

