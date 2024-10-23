#include "include/CollisionSystem.h"
#include "include/SphereCollider.h"
#include <tuple>
#include <cmath>

void CollisionSystem::ApplyCollisions()
{
	m_callbacksToCall.clear();
	for (auto i = m_colliders.begin(); i != m_colliders.end(); ++i)
	{
		for (auto j = std::next(i); j != m_colliders.end(); ++j)
		{
			std::tuple<Vector3f, double> result;
			if (SphereCollider::CheckCollision((*i), (*j), &result))
			{
				SphereCollider::ResolveCollision((*i), (*j), e, result);

				//Ajout a la liste d'appel
				m_callbacksToCall[&(*i)] = CollisionCallback{ (&(*j)) };
				m_callbacksToCall[&(*j)] = CollisionCallback{ (&(*i)) };
			}
		}
	}

	for (auto& i : m_callbacksToCall)
	{
		if(i.first)
			i.first->ColliderCallBack(i.second);
	}

}

void CollisionSystem::ApplyGroundCollisions()
{
	m_callbacksToCall.clear();
	for (auto i = m_colliders.begin(); i != m_colliders.end(); ++i)
	{
		SphereCollider c1 = *i;
		std::tuple<Vector3f, double> result;

		//Verification du sol
		if (SphereCollider::CheckCollisionGround(c1, yFloor, &result))
		{
			SphereCollider::ResolveCollision(c1, e, result);
		}

		if (c1.GetParticle()->GetPosition().y > yFloor)
			c1.GetParticle()->SetPosition(Vector3f(c1.GetParticle()->GetPosition().x, yFloor, 0));
	}
	
	for (auto& i : m_callbacksToCall)
	{
		if (i.first)
			i.first->ColliderCallBack(CollisionCallback{ nullptr });
	}
}

void CollisionSystem::ApplyCableCollisions()
{
	for (auto i = m_cables.begin(); i != m_cables.end(); ++i)
	{
		std::tuple<Vector3f, float> result;
		if (ParticleCable::CheckStretch((*i), &result))
		{
			ParticleCable::ResolveStretch((*i), e, std::get<1>(result), std::get<0>(result));
		}
	}
}

void CollisionSystem::ApplyStickCollisions()
{
	for (auto i = m_sticks.begin(); i != m_sticks.end(); ++i)
	{
		std::tuple<Vector3f, float> result;
		if (ParticleStick::CheckStretch((*i), &result))
		{
			ParticleStick::ResolveStretch((*i), e, std::get<1>(result), std::get<0>(result));
		}
	}
}

void CollisionSystem::AddCollider(float r, std::shared_ptr<Particle> particle)
{
	m_colliders.push_back(SphereCollider(r, particle));
}

void CollisionSystem::AddCable(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float cableLength)
{
	m_cables.push_back(ParticleCable(particle1, particle2, cableLength));
}

void CollisionSystem::AddStick(std::shared_ptr<Particle> particle1, std::shared_ptr<Particle> particle2, float sticklength)
{
	m_sticks.push_back(ParticleStick(particle1, particle2, sticklength));
}

