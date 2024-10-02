#pragma once
#include <iostream>
class IParticuleForceGenerator 
{
	class Particle;
	public :
		virtual void updateforce(Particle* particle, float duration) { std::cout << "lul"; };
};

