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
		SphereCollider c1 = *i;
		for (auto j = std::next(i); j != m_colliders.end(); ++j)
		{
			SphereCollider c2 = *j;
			std::tuple<Vector3f, float> result;
			if (SphereCollider::CheckCollision(c1, c2, &result))
			{
				//Calculer la nouvelle velocite avec K 
				Vector3f Vrel = c1.GetParticle()->GetVelocity() - c2.GetParticle()->GetVelocity();
				float K = (e + 1) * Vrel.DotProduct(std::get<0>(result)) / (c1.GetParticle()->GetInverseMass() + c2.GetParticle()->GetInverseMass());

				//Masses
				float masse1 = 1 / c1.GetParticle()->GetInverseMass();
				float masse2 = 1 / c2.GetParticle()->GetInverseMass();

				//Separation de la position post-collision
				float overlap = std::max(0.0f, -std::get<1>(result));
				Vector3f correction1 = std::get<0>(result) * overlap * (masse2 / (masse2 + masse1));
				Vector3f correction2 = std::get<0>(result) * overlap * (masse1 / (masse2 + masse1));

				c1.GetParticle()->SetPosition(c1.GetParticle()->GetPosition() + correction1);
				c2.GetParticle()->SetPosition(c2.GetParticle()->GetPosition() - correction2);

				//Impulsion
				Vector3f impulse = std::get<0>(result) * K;
				c1.GetParticle()->SetVelocity(c1.GetParticle()->GetVelocity() - impulse * c1.GetParticle()->GetInverseMass());
				c2.GetParticle()->SetVelocity(c2.GetParticle()->GetVelocity() + impulse * c2.GetParticle()->GetInverseMass());

				//Ajout a la liste d'appel
				m_callbacksToCall[&c1] = c2.GetParticle();
				m_callbacksToCall[&c2] = c1.GetParticle();
			}
		}
	}

	for (auto& i : m_callbacksToCall)
	{
		i.first->ColliderCallBack(i.second);
	}

}

void CollisionSystem::AddCollider(float r, std::shared_ptr<Particle> particle)
{
	m_colliders.push_back(SphereCollider(r, particle));
}
