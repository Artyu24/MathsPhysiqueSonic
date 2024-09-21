#pragma once
#include "Vector3.h"

class Particle
{
public:
	Particle(Vector3f position, Vector3f velocity, float mass, bool isIntegrateEuler);
	~Particle() = default;

	//Getter
	Vector3f GetPosition();
	Vector3f GetVelocity();
	Vector3f GetAcceleration();
	Vector3f GetPrevPosition();
	float GetSize() const;
	float GetInverseMass() const;

	//Setter
	void SetPosition(const Vector3f value);
	void SetVelocity(const Vector3f value);
	void SetAcceleration(const Vector3f value);
	void SetPrevPosition(const Vector3f value);
	void SetSize(const float value);

	//Physics Method
	void ApplyForce(Vector3f force);
	void Integrate(float deltaTime);

private:
	Vector3f m_position;
	Vector3f m_velocity;
	Vector3f m_acceleration;
	Vector3f m_prevPosition; //For Verlet purpose
	float m_invMass;
	float m_size;

	bool m_isIntegrateEuler = false;

	void IntegrateEuler(float deltaTime);
	void IntegrateVerlet(float deltaTime);
};





