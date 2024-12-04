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
	OcTree(Area area);
	~OcTree();

	void InsertSphere(std::shared_ptr<Sphere> newSphere);
	void GetAreas(std::vector<std::shared_ptr<Area>>& areas);

private:
	Area m_cubeArea;
	std::shared_ptr<Sphere> m_OcTreeSphere;

	std::vector<std::shared_ptr<Sphere>> m_objects;

	std::vector<std::shared_ptr<OcTree>> m_childs;

	void Divide();
};

