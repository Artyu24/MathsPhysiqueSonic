
#include "include/ParticleSpringFixedPoint.h"


ParticleSpringFixedPoint::ParticleSpringFixedPoint( const Vector3f& fixedPoint, float restLength, float springConstant, float maxStretch, bool isElastic)
    : fixedPoint(fixedPoint),
    restLength(restLength),
    springConstant(springConstant),
    maxStretch(maxStretch),
    isElastic(isElastic)
{
}


void ParticleSpringFixedPoint::UpdateForce(std::shared_ptr<Particle> particle, float duration)
{
    Vector3<float> forceDirection;

    // Si particleA est nullptr, on utilise le point fixe
    forceDirection = particle->GetPosition() - fixedPoint;


    float length = forceDirection.Length();
    float deltaLength = length - restLength;
    if ( length > maxStretch) {
        length = maxStretch;
    }

    
    // Loi de Hooke : F = -k * deltaX
    Vector3<float> force = forceDirection.Normalize() * (-springConstant * deltaLength);

    particle->AddForce(force);

}

// Getters


const Vector3f& ParticleSpringFixedPoint::GetFixedPoint() const {
    return fixedPoint;
}

float ParticleSpringFixedPoint::GetRestLength() const {
    return restLength;
}

float ParticleSpringFixedPoint::GetSpringConstant() const {
    return springConstant;
}

float ParticleSpringFixedPoint::GetMaxStretch() const {
    return maxStretch;
}

bool ParticleSpringFixedPoint::GetIsElastic() const {
    return isElastic;
}

// Setters
void ParticleSpringFixedPoint::SetFixedPoint(const Vector3f& point) {
    fixedPoint = point;
}

void ParticleSpringFixedPoint::SetRestLength(float length) {
    restLength = length;
}

void ParticleSpringFixedPoint::SetSpringConstant(float constant) {
    springConstant = constant;
}

void ParticleSpringFixedPoint::SetMaxStretch(float stretch) {
    maxStretch = stretch;
}

void ParticleSpringFixedPoint::SetIsElastic(bool elastic) {
    isElastic = elastic;
}

