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
		for (auto j = i; j != m_colliders.end(); ++j)
		{
			if (j == i)
				continue;

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

				std::cout << "Distance : " << std::get<1>(result) << std::endl;

				//Impulsion
				c1.GetParticle()->SetVelocity(c1.GetParticle()->GetVelocity() - (std::get<0>(result) * K) / masse1 );
				c2.GetParticle()->SetVelocity(c2.GetParticle()->GetVelocity() + (std::get<0>(result) * K) / masse2 );

				//Separation de la position post-collision
				Vector3f deplacement1 = std::get<0>(result) * std::get<1>(result) * (masse2 / (masse2 + masse1));
				c1.GetParticle()->SetPosition(c1.GetParticle()->GetPosition() + deplacement1);

				Vector3f deplacement2 = std::get<0>(result) * std::get<1>(result) * (masse1 / (masse1 + masse2));
				c2.GetParticle()->SetPosition(c2.GetParticle()->GetPosition() - deplacement2);

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
