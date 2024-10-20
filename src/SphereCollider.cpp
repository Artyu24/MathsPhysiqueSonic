#include "include/SphereCollider.h"
#include "include/Vector3.h"

SphereCollider::SphereCollider(float r, std::shared_ptr<Particle> particle, bool enabled) :
m_radius(r),
m_particle(particle),
m_isEnabled(enabled)
{
}

float SphereCollider::GetRadius() const { return m_radius; }

Particle* SphereCollider::GetParticle() const {	return m_particle.get(); }

bool SphereCollider::IsEnabled() const { return m_isEnabled; }

void SphereCollider::AddCollisionFunction(std::function<void(Particle*)> func)
{
	m_delegates.push_back(std::move(func));
}

void SphereCollider::ColliderCallBack(Particle* particule) const
{
	for (auto& i : m_delegates)
	{
		i(particule);
	}
}

bool SphereCollider::CheckCollision(SphereCollider& col1, SphereCollider& col2, std::tuple<Vector3f, double>* result)
{
	if (!col1.IsEnabled() || !col2.IsEnabled())
		return false;

	Vector3f distance = col2.m_particle->GetPosition() - col1.m_particle->GetPosition();
	Vector3f norme = distance.Normalize();
	
	double distSquared = distance.DotProduct(distance);
	double radiusSum = col1.GetRadius() + col2.GetRadius();
	if (distSquared < radiusSum * radiusSum) {
		*result = { norme, std::sqrt(distSquared) - radiusSum };
		return true;
	}
	return false;
}

