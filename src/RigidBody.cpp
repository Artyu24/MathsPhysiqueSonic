#include "RigidBody.h"
#include "include/Sphere.h"

RigidBody::RigidBody(std::shared_ptr<Particle> particle)
    : mass(1/particle->GetInverseMass()),
    centerOfMass(particle),
    //position(initialPosition), 
    orientation(Quaternion({1.0f, 0.f, 0.f, 0.f})),
    linearVelocity(Vector3f()), 
    angularVelocity(Vector3f()),
    force(Vector3f()), 
    torque(Vector3f()) 
{
    ComputeInertiaTensor();
    inverseInertiaTensor = inertiaTensor.InvertByRowReduction();

    Sphere SphereRb(centerOfMass, 50.f * sqrt(3)/2);
    std::shared_ptr<Sphere> sphereShared = std::make_shared<Sphere>(SphereRb);
    boundingSphere = sphereShared;

    Box BoxRb(centerOfMass, 50.0f);
    std::shared_ptr<Box> boxShared = std::make_shared<Box>(BoxRb);
    boundingBox = boxShared;

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
    centerOfMass->Integrate(deltaTime);
}

void RigidBody::UpdateOrientation(double deltaTime)
{
    Quaternion angularVelocityQuat(0.0f, angularVelocity.x, angularVelocity.y, angularVelocity.z);

    Quaternion deltaOrientation = angularVelocityQuat * orientation;
    deltaOrientation = deltaOrientation * 0.5f * deltaTime;
    orientation = (orientation + deltaOrientation).GetNormalize();
}

void RigidBody::UpdateLinearVelocity(double deltaTime) 
{
    /*Vector3f acceleration = force / mass;
    linearVelocity += acceleration * deltaTime;*/
    linearVelocity = centerOfMass->GetVelocity();
}

void RigidBody::UpdateAngularVelocity(double deltaTime) 
{
    Vector3f angularAcceleration = inverseInertiaTensor * torque;
    angularVelocity = angularAcceleration * deltaTime;
}

void RigidBody::ApplyForce(const Vector3f& appliedForce)
{
    centerOfMass->AddForce(force);
    //force += appliedForce;
}

void RigidBody::ApplyTorque(const Vector3f& appliedTorque)
{
    torque += appliedTorque;
}

void RigidBody::UpdateState(double deltaTime) 
{
    UpdatePosition(deltaTime);
    UpdateAngularVelocity(deltaTime);
    UpdateOrientation(deltaTime);
    UpdateLinearVelocity(deltaTime);
    

    // reset du vecteur force et torque
    torque = { 0.f,0.f,0.f };
}

// Getters
double RigidBody::GetMass() const 
{
    return mass;
}

Vector3f RigidBody::GetPosition() const 
{
    return centerOfMass->GetPosition();
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

std::shared_ptr<Particle> RigidBody::GetCenterOfMass() const {
    return centerOfMass;
}

std::shared_ptr<Sphere> RigidBody::GetBoundingSphere() const {
    return boundingSphere;
}

std::shared_ptr<Box> RigidBody::GetBoundingBox() const {
    return boundingBox;
}

void RigidBody::SetBoundingSphereSize(float radius)
{
    this->boundingSphere->SetRadius(radius);
}

void RigidBody::SetBoundingBoxSize(float size)
{
    this->boundingBox->SetSize(size);
}