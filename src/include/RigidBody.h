#pragma once

#include "include/Matrix.h"
#include "include/Quaternion.h"
#include "include/Vector3.h"

class RigidBody {
public:
    // Constructor
    RigidBody(double mass, const Vector3f& initialPosition);

    // Public methods
    void computeInertiaTensor();
    
    void updatePosition(double deltaTime);
    void updateOrientation(double deltaTime);
    
    void updateLinearVelocity(double deltaTime);
    void updateAngularVelocity(double deltaTime);

    void applyForce(const Vector3f& appliedForce);
    void applyTorque(const Vector3f& appliedTorque);
    
    void updateState(double deltaTime);

    // Getters
    double getMass() const;
    Vector3f getPosition() const;
    Quaternion getOrientation() const;
    Vector3f getLinearVelocity() const;
    Vector3f getAngularVelocity() const;

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