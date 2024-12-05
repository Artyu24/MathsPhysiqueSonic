#pragma once
#include <array>
#include <memory>
#include <vector>

#include "Area.h"
#include "Sphere.h"

class OcTree
{
public:
	OcTree() = default;
	OcTree(Area area, int depth);
	~OcTree();

	void InsertSphere(std::shared_ptr<Sphere> newSphere);
	void GetQuads(std::vector<std::shared_ptr<OcTree>>& quads);

	Area GetArea() { return m_cubeArea; }
	int GetDepth() { return m_depth; }

private:
	Area m_cubeArea;
	std::shared_ptr<Sphere> m_OcTreeSphere;

	std::vector<std::shared_ptr<Sphere>> m_objects;
	std::vector<std::shared_ptr<OcTree>> m_childs;

	int m_depth;

	void Divide();
};

