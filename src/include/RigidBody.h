#pragma once

#include "include/Matrix.h"
#include "include/Quaternion.h"
#include "include/Vector3.h"
#include "include/Particle.h"
#include "include/Sphere.h"
#include "include/Box.h"
#include <memory>

class RigidBody {
public:
    // Constructor
    RigidBody(std::shared_ptr<Particle> particle);

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
    std::shared_ptr<Particle> GetCenterOfMass() const;
    std::shared_ptr<Sphere> GetBoundingSphere() const;
    std::shared_ptr<Box> GetBoundingBox() const;

private:
    // Attributes
    float mass;
    std::shared_ptr<Particle> centerOfMass;
    Quaternion orientation;
    Vector3f linearVelocity;
    Vector3f angularVelocity;
    Matrix inertiaTensor;
    Matrix inverseInertiaTensor;
    Vector3f force;
    Vector3f torque;

    std::shared_ptr<Sphere> boundingSphere;
    std::shared_ptr<Box> boundingBox;
};
