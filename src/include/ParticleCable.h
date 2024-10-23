#pragma once

#include "ParticleLink.h"
#include <tuple>

class ParticleCable : public ParticleLink
{
	public :
		ParticleCable(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float maxlength);

		static bool CheckStretch(ParticleCable cable, std::tuple<Vector3f, float>* result);
		static void ResolveStretch(ParticleCable cable, float restitution, float distance, Vector3f normal);

		float GetMaxLength() const;

	private:
		float m_maxlength;
};

