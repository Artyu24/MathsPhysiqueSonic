#pragma once
#include <array>
#include <memory>
#include <vector>

#include "Area.h"
#include "Box.h"
#include "CollisionSystem.h"
#include "RigidBody.h"
#include "Sphere.h"

class OcTree
{
public:

	class ObjectCollision
	{
	public:
		std::shared_ptr<Sphere> Sphere;
		std::shared_ptr<Box> Box;
		
	};

	OcTree() = default;
	OcTree(Area area, int depth, CollisionSystem colSys);
	~OcTree();

	void InsertObject(std::shared_ptr<RigidBody> newData);
	void GetQuads(std::vector<std::shared_ptr<OcTree>>& quads);
	void TestCollision();


	Area GetArea() { return m_cubeArea; }
	int GetDepth() { return m_depth; }
	


private:
	CollisionSystem m_colSys;

	Area m_cubeArea;
	std::shared_ptr<RigidBody> rigidBody;
	std::shared_ptr<Sphere> m_OcTreeSphere;
	std::shared_ptr<Box> m_OcTreeBox;
	std::vector<std::shared_ptr<RigidBody>> m_objects;
	std::vector<std::shared_ptr<OcTree>> m_childs;

	int m_depth;

	void Divide();
};

