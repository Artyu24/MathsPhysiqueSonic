#include "RigidBody.h"

RigidBody::RigidBody(double mass, const Vector3f& initialPosition)
    : mass(mass), position(initialPosition), orientation(Quaternion()),
    linearVelocity(Vector3f()), angularVelocity(Vector3f()),
    force(Vector3f()), torque(Vector3f()) 
{
    computeInertiaTensor();
    inverseInertiaTensor = inertiaTensor.InvertByRowReduction();
}

void RigidBody::computeInertiaTensor() 
{
    // exemple avec cube 
    float sideLength = 1.0f; 
    float inertiaValue = (1.0 / 6.0) * mass * (sideLength * sideLength);

    inertiaTensor = Matrix(3, 3, {
        inertiaValue, 0.0, 0.0,
        0.0, inertiaValue, 0.0,
        0.0, 0.0, inertiaValue
        });

    inverseInertiaTensor = inertiaTensor.InvertByRowReduction();
}

void RigidBody::updatePosition(double deltaTime) 
{
    position += linearVelocity * deltaTime;
}

void RigidBody::updateOrientation(double deltaTime)
{
    
}

void RigidBody::updateLinearVelocity(double deltaTime) 
{
    Vector3f acceleration = force / mass;
    linearVelocity += acceleration * deltaTime;
}

void RigidBody::updateAngularVelocity(double deltaTime) 
{
    Vector3f angularAcceleration = inverseInertiaTensor * torque;
    angularVelocity += angularAcceleration * deltaTime;
}

void RigidBody::applyForce(const Vector3f& appliedForce)
{
    force += appliedForce;
}

void RigidBody::applyTorque(const Vector3f& appliedTorque)
{
    torque += appliedTorque;
}

void RigidBody::updateState(double deltaTime) 
{
    updatePosition(deltaTime);
    updateOrientation(deltaTime);
    updateLinearVelocity(deltaTime);
    updateAngularVelocity(deltaTime);

    // reset du vecteur force et torque
    force = Vector3f();
    torque = Vector3f();
}

// Getters
double RigidBody::getMass() const 
{
    return mass;
}

Vector3f RigidBody::getPosition() const 
{
    return position;
}

Quaternion RigidBody::getOrientation() const 
{
    return orientation;
}

Vector3f RigidBody::getLinearVelocity() const 
{
    return linearVelocity;
}

Vector3f RigidBody::getAngularVelocity() const 
{
    return angularVelocity;
}