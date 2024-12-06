#include "Box.h"
#include "Particle.h"
#include "Vector3.h"

Box::Box(std::shared_ptr<Particle> particle, float size) :
m_particle(particle),
m_size(size)
{
}

float Box::GetSize() const
{
	return m_size;
}

Vector3f Box::GetCenter() const
{
	return m_particle->GetPosition();
}

std::array<Vector3f, 8> Box::GetBoxVertices() const
{
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
		vertice *= m_size;
		vertice += m_particle.get()->GetPosition();
	}

	return verticeArray;
}
