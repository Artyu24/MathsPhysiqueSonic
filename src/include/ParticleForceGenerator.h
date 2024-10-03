#pragma once
#include <iostream>

#include "Particle.h"

class IParticleForceGenerator 
{
	public :
		virtual void UpdateForce(Particle* particle, float duration) = 0;
};

