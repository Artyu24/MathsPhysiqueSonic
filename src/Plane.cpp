#include "Plane.h"

Plane::Plane(const Vector3f normal, const Vector3f& center, float planeDistance) :
m_normal(normal)
{
	m_point = normal * planeDistance + center;
}

Vector3f Plane::GetNormal() const
{
	return m_normal;
}

Vector3f Plane::GetPoint() const
{
	return m_point;
}
