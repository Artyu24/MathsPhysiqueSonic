#pragma once
#include "src/include/Vector3.h"

class Particle
{
	public:
		Particle(Vector3<float> position, float size);
		~Particle();

	Vector3<float> GetPosition();
	Vector3<float> GetVelocity();
	Vector3<float> GetAcceleration();

	float GetSize();
	float GetInverseMass();

	void SetPosition(const Vector3<float> value);
	void SetVelocity(const Vector3<float> value);
	void SetAcceleration(const Vector3<float> value);

	void SetSize(const float value);


private:
	Vector3<float> m_position;
	Vector3<float> m_velocity;
	Vector3<float> m_acceleration;

	float m_invMass;
	float m_size;

};





