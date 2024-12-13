#include "include/CollisionSystem.h"
#include "include/SphereCollider.h"
#include "include/CollisionCallback.h"
#include "include/Box.h"
#include "include/RigidBody.h"
#include "include/Plane.h"
#include "ParticuleCollision.h"
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

void CollisionSystem::ApplyBoxCollision(const RigidBody& rb1, const RigidBody& rb2) {
	// Variable des informations de collision
	CollisionCallback3D infos;

	// V�rification de la collision entre les deux bo�tes
 	if (CheckCollisionBox(rb1, rb2, infos)) {
		auto particle1 = rb1.GetBoundingBox()->GetParticle();
		auto particle2 = rb2.GetBoundingBox()->GetParticle();
		infos.restitution = 1.f;
		// Cas o� les deux RigidBody sont des plans
		if (particle1->GetIsPlane() && particle2->GetIsPlane()) {
			return;
		}
		// Cas o� le premier RigidBody est un plan
		if (particle1->GetIsPlane() && !particle2->GetIsPlane()) {
			infos.normal.Normalize();
			// Corriger la direction de la normale si n�cessaire
			if (particle1->GetPosition().DotProduct(infos.normal) > 0.0f) {
				infos.normal = -infos.normal;
			}
			// S'assurer que l'overlap est positif
			infos.overlap = std::abs(infos.overlap);
			// Limiter la restitution � une valeur r�aliste
			infos.restitution = std::clamp(infos.restitution, 0.0f, 0.8f);
			ParticuleCollision collision(particle2, infos.restitution, infos.overlap, infos.normal);
			collision.ApplyCollision();
		}
		else if (particle2->GetIsPlane() && !particle1->GetIsPlane()) {
			ParticuleCollision collision(particle1, infos.restitution, std::abs(infos.overlap), infos.normal);
			collision.ApplyCollision();
		}
		// Cas g�n�ral (deux objets dynamiques)
		else {
			ParticuleCollision collision(
				particle1, particle2, infos.restitution, std::abs(infos.overlap), infos.normal
			);
			collision.ApplyCollision();
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

bool CollisionSystem::CheckCollisionBox(const RigidBody& rb1, const RigidBody& rb2, CollisionCallback3D& callback)
{
	std::array<Vector3f, 8> vertices = rb2.GetBoundingBox()->GetBoxVertices(rb2);

	// Centre de la bo�te 1
	const Vector3f& box1Center = rb1.GetBoundingBox()->GetCenter();

	// Variables pour stocker le sommet en collision le plus proche
	float minDistanceSquared = std::numeric_limits<float>::max();
	Vector3f closestVertex;
	std::tuple<float, Vector3f, Vector3f> bestCollisionResult;

	for (const auto& vertex : vertices)
	{
		std::tuple<float, Vector3f, Vector3f> collisionResult;
		if (CheckVertexInsideBox(rb1, vertex, collisionResult))
		{
			// Calculer la distance carr�e du sommet au centre de la bo�te 1
			float distanceSquared = (vertex - box1Center).SquaredLength();

			// Si ce sommet est plus proche, mettre � jour le meilleur r�sultat
			if (distanceSquared < minDistanceSquared)
			{
				minDistanceSquared = distanceSquared;
				closestVertex = vertex;
				bestCollisionResult = collisionResult;
			}
		}
	}

	if (minDistanceSquared != std::numeric_limits<float>::max())
	{
		callback.overlap = std::get<0>(bestCollisionResult);
		callback.impactPoint = std::get<1>(bestCollisionResult);
		callback.normal = (rb1.GetPosition() - rb2.GetPosition()).Normalize();
		return true;
	}

	return false;
}

bool CollisionSystem::CheckCollisionPlane(const RigidBody& rb, const Plane& plane, CollisionCallback3D& calback)
{
	std::array<Vector3f, 8> vertices = rb.GetBoundingBox()->GetBoxVertices(rb);

	return false;
}

bool CollisionSystem::CheckVertexInsideBox(const RigidBody& rb, Vector3f vertex, std::tuple<float, Vector3f, Vector3f>& result)
{
	const Vector3f& boxCenter = rb.GetBoundingBox()->GetCenter();
	const float boxSize = rb.GetBoundingBox()->GetSize();

	float maxDistanceSquared = -1.0f;
	std::tuple<float, Vector3f, Vector3f> bestResult;

	for (const Vector3f& face : faces)
	{
		// Initialisation du plan bas� sur une face
		Plane facePlane(face, boxCenter, boxSize / 2.f);

		const Vector3f vertexToPlane = vertex - facePlane.GetPoint();
		float interpenetration = facePlane.GetNormal().DotProduct(vertexToPlane);

		// Si interpenetration est superieur a 0, on se trouve a l'exterieur de la box
		if (interpenetration > 0)
			return false;

		// Calcul de la distance au centre pour determiner la face associee
		float distanceSquared = (vertex - boxCenter).SquaredLength();

		if (distanceSquared > maxDistanceSquared)
		{
			maxDistanceSquared = distanceSquared;

			// Calcul du point d'impact
			Vector3f impactPoint = facePlane.GetPoint() - (facePlane.GetNormal() * interpenetration);

			// Mise � jour du meilleur r�sultat
			bestResult = { interpenetration, impactPoint, facePlane.GetNormal() };
		}
		
	}
	
	// Mise � jour du r�sultat final
	result = bestResult;
	return true;
}

bool CollisionSystem::CheckVertexPlane(const Vector3f& vertex, const Plane& plane, std::tuple<float, Vector3f, Vector3f>& result)
{
	float maxDistanceSquared = -1.0f;
	std::tuple<float, Vector3f, Vector3f> bestResult;

	const Vector3f vertexToPlane = vertex - plane.GetPoint();
	float interpenetration = plane.GetNormal().DotProduct(vertexToPlane);
	
	// Si interpenetration est superieur a 0, on se trouve a l'exterieur de la box
	if (interpenetration > 0)
		return false;

	Vector3f impactPoint = plane.GetPoint() - (plane.GetNormal() * interpenetration);

	// Mise � jour du meilleur r�sultat
	bestResult = { interpenetration, impactPoint, plane.GetNormal() };

	// Mise � jour du r�sultat final
	result = bestResult;
	return true;
}