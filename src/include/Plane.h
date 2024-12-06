#pragma once

#include "Vector3.h"

class Plane
{
	public:
		//normal du plan => la face du cube
		//center -> le centre du cube 
		//planedistance -> la taille du cube
		explicit Plane(const Vector3f normal, const Vector3f& center, float planeDistance);

		Vector3f GetNormal() const;
		Vector3f GetPoint() const;

	private:
		Vector3f m_normal;
		Vector3f m_point;
};

