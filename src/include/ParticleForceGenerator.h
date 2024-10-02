#pragma once
#include <iostream>
class IParticleForceGenerator 
{
	class Particle;
	public :
		virtual void updateforce(Particle* particle, float duration) { std::cout << "lul"; };
};

