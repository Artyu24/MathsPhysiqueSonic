#include "include/SphereCollider.h"
#include "include/ParticuleCollision.h"
#include "include/Vector3.h"

SphereCollider::SphereCollider(float r, std::shared_ptr<Particle> particle, bool enabled) :
m_radius(r),
m_particle(particle),
m_isEnabled(enabled)
{
}

float SphereCollider::GetRadius() const { return m_radius; }

void SphereCollider::SetRadius(float radius)
{
	m_radius = radius;
}

std::shared_ptr<Particle> SphereCollider::GetParticle() const {	return m_particle; }

bool SphereCollider::IsEnabled() const { return m_isEnabled; }

void SphereCollider::AddCollisionFunction(std::function<void(CollisionCallback)> func)
{
	m_delegates.push_back(std::move(func));
}

void SphereCollider::ColliderCallBack(CollisionCallback callback) const
{
	for (auto& i : m_delegates)
	{
		i(callback);
	}
}

bool SphereCollider::CheckCollision(SphereCollider& col1, SphereCollider& col2, std::tuple<Vector3f, double>* result)
{
	if (!col1.IsEnabled() || !col2.IsEnabled())
		return false;

	Vector3f distance = col1.m_particle->GetPosition() - col2.m_particle->GetPosition();
	Vector3f norme = distance.Normalize();
	
	double distSquared = distance.DotProduct(distance);
	double radiusSum = col1.GetRadius() + col2.GetRadius();
	if (distSquared < radiusSum * radiusSum) {
		*result = { norme, std::sqrt(distSquared) - radiusSum };
		return true;
	}
	return false;
}

bool SphereCollider::CheckCollisionGround(SphereCollider& col1, float groundY, std::tuple<Vector3f, double>* result)
{
	if (!col1.IsEnabled())
		return false;

	if (col1.GetParticle()->GetPosition().y >= groundY)
	{
		Vector3f distance = col1.m_particle->GetPosition() - Vector3{ 0.f, groundY, 0.f };
		*result = { Vector3f{0.f, 1.0f, 0.f}, distance.Length() - col1.GetRadius() };
		return true;
	}

	return false;
}

void SphereCollider::ResolveCollision(SphereCollider& col1, SphereCollider& col2, float restitution, std::tuple<Vector3f, double> info)
{
	ParticuleCollision collision(col1.GetParticle(), col2.GetParticle(), restitution, std::get<1>(info));
	collision.ApplyCollision();
}

void SphereCollider::ResolveCollision(SphereCollider& col1, float restitution, std::tuple<Vector3f, double> info)
{
	ParticuleCollision collision(col1.GetParticle(), restitution, std::get<1>(info));
	collision.ApplyCollision();
}

