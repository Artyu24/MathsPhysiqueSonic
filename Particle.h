#pragma once
#include "src/include/Vector3.h"

class Particle
{
	public:
		Particle(Vector3<float> position, Vector3<float> velocity, float size, float mass);
		~Particle() = default;

	
	Vector3<float> GetPosition();
	Vector3<float> GetVelocity();
	Vector3<float> GetAcceleration();
	Vector3<float> GetPrevPosition();

	float GetSize();
	float GetInverseMass();

	void SetPosition(const Vector3<float> value);
	void SetVelocity(const Vector3<float> value);
	void SetAcceleration(const Vector3<float> value);
	void SetPrevPosition(const Vector3<float> value);

	void SetSize(const float value);

	void integrateurEuler(float deltaTime);
	void integrateurVerlet(float deltaTime);

private:
	Vector3<float> m_position;
	Vector3<float> m_velocity;
	Vector3<float> m_acceleration;
	Vector3<float> m_prevPosition;

	float m_invMass;
	float m_size;

};





