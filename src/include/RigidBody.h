#pragma once

#include "include/Matrix.h"
#include "include/Quaternion.h"
#include "include/Vector3.h"

class RigidBody {
public:
    // Constructor
    RigidBody(double mass, const Vector3f& initialPosition);

    // Public methods
    void ComputeInertiaTensor();
    
    void UpdatePosition(double deltaTime);
    void UpdateOrientation(double deltaTime);
    
    void UpdateLinearVelocity(double deltaTime);
    void UpdateAngularVelocity(double deltaTime);

    void ApplyForce(const Vector3f& appliedForce);
    void ApplyTorque(const Vector3f& appliedTorque);
    
    void UpdateState(double deltaTime);

    // Getters
    double GetMass() const;
    Vector3f GetPosition() const;
    Quaternion GetOrientation() const;
    Vector3f GetLinearVelocity() const;
    Vector3f GetAngularVelocity() const;

private:
    // Attributes
    double mass;
    Vector3f position;
    Quaternion orientation;
    Vector3f linearVelocity;
    Vector3f angularVelocity;
    Matrix inertiaTensor;
    Matrix inverseInertiaTensor;
    Vector3f force;
    Vector3f torque;
};
