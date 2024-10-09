#pragma once
#include <iostream>

#include "Particle.h"

class IParticleForceGenerator 
{
	public :
		virtual void UpdateForce(std::shared_ptr<Particle> particle, float duration) = 0;
};

