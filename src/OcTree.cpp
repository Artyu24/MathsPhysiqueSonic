#include "OcTree.h"

#include "Particle.h"

OcTree::OcTree(Area area) :
m_cubeArea(area)
{
	Particle particle(area.pos);
	Sphere sphere(area.sideSize * sqrt(3), std::make_shared<Particle>(particle));
	m_OcTreeSphere = make_shared<Sphere>(sphere);
}

OcTree::~OcTree()
{
	m_OcTreeSphere = nullptr;
	m_objects.clear();
	m_childs.clear();
}

void OcTree::InsertSphere(std::shared_ptr<Sphere> newSphere)
{
	if(!m_OcTreeSphere->IsColliding(newSphere))
		return;

	if (m_childs.size() == 0)
		m_objects.push_back(newSphere);
	else
	{
		for(auto ocTreeChild : m_childs)
		{
			ocTreeChild->InsertSphere(newSphere);
		}

		return;
	}

	if(m_objects.size() > 10)
	{
		Divide();

		for (auto ocTreeChild : m_childs)
		{
			for (auto sphere : m_objects)
			{
				ocTreeChild->InsertSphere(sphere);
			}
		}

		m_objects.clear();
	}
}

void OcTree::GetAreas(std::vector<std::shared_ptr<Area>>& areas)
{
	if (m_childs.size() != 0)
	{
		for (auto ocTreeChild : m_childs)
			ocTreeChild->GetAreas(areas);
	}
	else
		areas.emplace_back(std::make_shared<Area>(m_cubeArea));
}

void OcTree::Divide()
{
	float newSideSize = m_cubeArea.sideSize / 2;
	float posDivide = m_cubeArea.sideSize / 4;

	float xMore = m_cubeArea.pos.x + posDivide;
	float xMinus = m_cubeArea.pos.x - posDivide;
	float yMore = m_cubeArea.pos.y + posDivide;
	float yMinus = m_cubeArea.pos.y - posDivide;
	float zMore = m_cubeArea.pos.z + posDivide;
	float zMinus = m_cubeArea.pos.z - posDivide;

	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMore, zMore), newSideSize))));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMore, zMinus), newSideSize))));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMinus, zMore), newSideSize))));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMinus, zMinus), newSideSize))));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMore, zMore), newSideSize))));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMore, zMinus), newSideSize))));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMinus, zMore), newSideSize))));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMinus, zMinus), newSideSize))));
}
