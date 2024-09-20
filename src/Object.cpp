#include "include/Object.h"

Object::Object() :
m_image(), m_pos()
{
}

ofImage& Object::GetImage()
{
	return m_image;
}

float Object::GetImageWidth() const
{
	return m_image.getWidth();
}

float Object::GetImageHeight() const
{
	return m_image.getHeight();
}

Vector3f& Object::GetPosition()
{
	return m_pos;
}

void Object::SetPosition(const Vector3f& pos)
{
	m_pos = pos;
}
