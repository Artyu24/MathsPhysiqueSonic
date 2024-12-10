#include "Box.h"
#include "Particle.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "RigidBody.h"

Box::Box(std::shared_ptr<Particle> particle, float size, float restitution) :
m_particle(particle),
m_size(size),
m_restitution(restitution)
{
}

float Box::GetSize() const
{
	return m_size;
}

float Box::GetRestitution() const
{
	return m_restitution;
}

Vector3f Box::GetCenter() const
{
	return m_particle->GetPosition();
}

std::shared_ptr<Particle> Box::GetParticle() const
{
	return m_particle;
}

std::array<Vector3f, 8> Box::GetBoxVertices(const RigidBody &rb) const
{
	Quaternion rotation = rb.GetOrientation();

	std::array<Vector3f, 8> verticeArray
	{
		//Upper vertices
		Vector3f{-1.f,  1.f,  1.f},
		Vector3f{ 1.f,  1.f,  1.f},
		Vector3f{ 1.f,  1.f, -1.f},
		Vector3f{-1.f,  1.f, -1.f},
		//Lower vertices
		Vector3f{-1.f, -1.f,  1.f},
		Vector3f{ 1.f, -1.f,  1.f},
		Vector3f{ 1.f, -1.f, -1.f},
		Vector3f{-1.f, -1.f, -1.f}
	};

	for (auto& vertice : verticeArray)
	{
		Quaternion::RotateVector(rotation, vertice);
		vertice *= m_size / 2.f;
		vertice += m_particle.get()->GetPosition();
	}

	return verticeArray;
}
