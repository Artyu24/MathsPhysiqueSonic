#include "Box.h"
#include "Particle.h"

Box::Box(std::shared_ptr<Particle> particle, float size) :
m_particle(particle),
m_size(size)
{
}

const bool Box::IsColliding(const Box& otherBox, CollisionCallback& results)
{
	return IsCollidingStatic(*this, otherBox, results);
}

const bool Box::IsCollidingStatic(const Box& first, const Box& second, CollisionCallback& results)
{
	return false;
}
