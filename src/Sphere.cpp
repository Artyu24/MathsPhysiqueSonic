#include "Sphere.h"
#include "Particle.h"

Sphere::Sphere(float radius, std::shared_ptr<Particle> particle) :
m_radius(radius),
m_particle(particle)
{
}

float Sphere::GetRadius() const
{
	return m_radius;
}

std::shared_ptr<Particle> Sphere::GetParticle() const
{
	return m_particle;
}

const bool Sphere::IsColliding(std::shared_ptr<Sphere>& otherSphere)
{
	return IsCollidingStatic(shared_from_this(), otherSphere);
}

const bool Sphere::IsCollidingStatic(std::shared_ptr<Sphere>& first, std::shared_ptr<Sphere>& second)
{
	Vector3f distance = first->GetParticle()->GetPosition() - second->GetParticle()->GetPosition();
	Vector3f norme = distance.Normalize();

	double distSquared = distance.DotProduct(distance);
	double radiusSum = first->GetRadius() + second->GetRadius();
	if (distSquared < radiusSum * radiusSum) {
		return true;
	}
	return false;
}
