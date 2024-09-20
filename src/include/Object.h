#pragma once
#include "ofMain.h"
#include "Vector3.h"

class Object
{
public:
	Object();

	ofImage& GetImage();
	float GetImageWidth() const;
	float GetImageHeight() const;
	Vector3f& GetPosition();

	void SetPosition(const Vector3f& pos);

private:
	ofImage m_image;
	Vector3f m_pos;
};
