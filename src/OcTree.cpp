#include "OcTree.h"

#include "Particle.h"
#include "include/RigidBody.h"

OcTree::OcTree(Area area, int depth, CollisionSystem colSys) :
m_cubeArea(area),
m_depth(depth),
m_colSys(colSys)
{

	Particle particle(area.pos);
	Sphere sphere(std::make_shared<Particle>(particle), area.sideSize * sqrt(3)/2);
	m_OcTreeSphere = make_shared<Sphere>(sphere);

	Box box(std::make_shared<Particle>(particle), area.sideSize);
	m_OcTreeBox = make_shared<Box>(box);
}

OcTree::~OcTree()
{
	m_OcTreeSphere = nullptr;
	m_objects.clear();
	m_childs.clear();
}

void OcTree::InsertObject(std::shared_ptr<RigidBody> newData)
{
	if (!m_OcTreeSphere->IsColliding(*newData->GetBoundingSphere()))
		return;

	if (m_childs.size() == 0)
		
		m_objects.push_back(newData);
	else
	{
		for(auto ocTreeChild : m_childs)
		{
			ocTreeChild->InsertObject(newData);
		}

		return;
	}

	if(m_objects.size() > 10)
	{
		Divide();

		for (auto ocTreeChild : m_childs)
		{
			for (auto obj : m_objects)
			{
				ocTreeChild->InsertObject(obj);
			}
		}

		m_objects.clear();
	}
}

void OcTree::GetQuads(std::vector<std::shared_ptr<OcTree>>& quads)
{
	if (m_childs.size() != 0)
	{
		for (auto ocTreeChild : m_childs)
			ocTreeChild->GetQuads(quads);
	}
	else
		quads.emplace_back(std::make_shared<OcTree>(*this));
}

void OcTree::TestCollision()
{
	if (m_childs.size() != 0)
	{
		for (auto ocTreeChild : m_childs)
		{
			ocTreeChild->TestCollision();
		}

		return;
	}

	if(m_objects.size() <= 1)
		return;

	for (int i = 0; i < m_objects.size(); i++)
	{
		auto c1 = m_objects[i];

		for (int j = i + 1; j < m_objects.size(); j++)
		{
			auto c2 = m_objects[j];

			m_colSys.ApplyBoxCollision(*m_objects[i], *m_objects[j]);
		}
	}
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

	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMore, zMore), newSideSize), m_depth++, m_colSys)));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMore, zMinus), newSideSize), m_depth++, m_colSys)));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMinus, zMore), newSideSize), m_depth++, m_colSys)));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMinus, yMinus, zMinus), newSideSize), m_depth++, m_colSys)));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMore, zMore), newSideSize), m_depth++, m_colSys)));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMore, zMinus), newSideSize), m_depth++, m_colSys)));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMinus, zMore), newSideSize), m_depth++, m_colSys)));
	m_childs.push_back(std::make_shared<OcTree>(OcTree(Area(Vector3f(xMore, yMinus, zMinus), newSideSize), m_depth++, m_colSys)));
}

//void OcTree::SetRigidBody(std::shared_ptr<RigidBody> rigidBody)
//{
//	this->RigidBody = rigidBody;
//}

//std::shared_ptr<RigidBody> Octree::GetRigidBody() const
//{
//	return this->RigidBody;
//}