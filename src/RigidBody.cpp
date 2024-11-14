#include "RigidBody.h"

RigidBody::RigidBody(double mass, const Vector3f& initialPosition)
    : mass(mass),
    centerOfMass(initialPosition, Vector3f(), mass, 0.98f, true),
    //position(initialPosition), 
    orientation(Quaternion()),
    linearVelocity(Vector3f()), 
    angularVelocity(Vector3f()),
    force(Vector3f()), 
    torque(Vector3f()) 
{
    ComputeInertiaTensor();
    inverseInertiaTensor = inertiaTensor.InvertByRowReduction();
}

void RigidBody::ComputeInertiaTensor() 
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

void RigidBody::UpdatePosition(double deltaTime) 
{
    //position += linearVelocity * deltaTime;
    centerOfMass.Integrate(deltaTime);
}

void RigidBody::UpdateOrientation(double deltaTime)
{
    float angle = angularVelocity.Length() * deltaTime;
    Vector3f axis = angularVelocity.Normalize();

    Quaternion deltaOrientation = Quaternion::GetRotationQuaternion(angle, axis);
    orientation = (deltaOrientation * orientation).GetNormalize();
}

void RigidBody::UpdateLinearVelocity(double deltaTime) 
{
    /*Vector3f acceleration = force / mass;
    linearVelocity += acceleration * deltaTime;*/
    linearVelocity = centerOfMass.GetVelocity();
}

void RigidBody::UpdateAngularVelocity(double deltaTime) 
{
    Vector3f angularAcceleration = inverseInertiaTensor * torque;
    angularVelocity += angularAcceleration * deltaTime;
}

void RigidBody::ApplyForce(const Vector3f& appliedForce)
{
    centerOfMass.AddForce(force);
    //force += appliedForce;
}

void RigidBody::ApplyTorque(const Vector3f& appliedTorque)
{
    torque += appliedTorque;
}

void RigidBody::UpdateState(double deltaTime) 
{
    UpdatePosition(deltaTime);
    UpdateOrientation(deltaTime);
    UpdateLinearVelocity(deltaTime);
    UpdateAngularVelocity(deltaTime);

    // reset du vecteur force et torque
    //force = Vector3f();
    torque = Vector3f();
}

// Getters
double RigidBody::GetMass() const 
{
    return mass;
}

Vector3f RigidBody::GetPosition() const 
{
    return centerOfMass.GetPosition();
}

Quaternion RigidBody::GetOrientation() const 
{
    return orientation;
}

Vector3f RigidBody::GetLinearVelocity() const 
{
    return linearVelocity;
}

Vector3f RigidBody::GetAngularVelocity() const 
{
    return angularVelocity;
}