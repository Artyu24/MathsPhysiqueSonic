#include "include/CollisionSystem.h"
#include "include/SphereCollider.h"
#include "include/Vector3.h"
#include "include/Particle.h"
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
				m_callbacksToCall[&(*i)] = (*j).GetParticle();
				m_callbacksToCall[&(*j)] = (*i).GetParticle();
			}
		}
	}

	for (auto& i : m_callbacksToCall)
	{
		if(i.second)
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
		if (i.second)
			i.first->ColliderCallBack(nullptr);
	}
}

void CollisionSystem::AddCollider(float r, std::shared_ptr<Particle> particle)
{
	m_colliders.push_back(SphereCollider(r, particle));
}
