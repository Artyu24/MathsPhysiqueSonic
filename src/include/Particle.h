#pragma once
#include "Vector3.h"

class Particle
{
public:
	Particle(Vector3f position, Vector3f velocity, float mass, float damping, bool isIntegrateEuler);

	//Getter
	Vector3f GetPosition() const;
	Vector3f GetVelocity() const;
	Vector3f GetAcceleration() const;
	Vector3f GetPrevPosition() const;
	float GetSize() const;
	float GetInverseMass() const;
	float GetDamping() const;
	bool GetIsIntegrateEuler() const;

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
	float m_damping;

	bool m_isIntegrateEuler = false;

	void IntegrateEuler(float deltaTime);
	void IntegrateVerlet(float deltaTime);
};





