
#include "include/ParticleSpring.h"

ParticleSpring::ParticleSpring(Particle* particleA, const Vector3f& fixedPoint, float restLength, float springConstant, float maxStretch, bool isElastic)
    : particleA(particleA ? particleA : nullptr), 
    fixedPoint(fixedPoint),
    restLength(restLength),
    springConstant(springConstant),
    maxStretch(maxStretch),
    isElastic(isElastic)
{
}


void ParticleSpring::UpdateForce(Particle* particle, float duration)
{
    Vector3<float> forceDirection;

    // Si particleA est nullptr, on utilise le point fixe
    if (particleA) {
        forceDirection = particle->GetPosition() - particleA->GetPosition();
    }
    else {
        forceDirection = particle->GetPosition() - fixedPoint;
    }

    float length = forceDirection.Length();
    float deltaLength = length - restLength;

    if (isElastic && length > maxStretch) {
        length = maxStretch;  
    }

    // Loi de Hooke : F = -k * deltaX
    Vector3<float> force = forceDirection.Normalize() * (-springConstant * deltaLength);

    particle->ApplyForce(force);

    if (particleA) {
        particleA->ApplyForce(-force);
    }
}

// Getters
Particle* ParticleSpring::GetParticleA() const {
    return particleA;
}

const Vector3f& ParticleSpring::GetFixedPoint() const {
    return fixedPoint;
}

float ParticleSpring::GetRestLength() const {
    return restLength;
}

float ParticleSpring::GetSpringConstant() const {
    return springConstant;
}

float ParticleSpring::GetMaxStretch() const {
    return maxStretch;
}

bool ParticleSpring::GetIsElastic() const {
    return isElastic;
}

// Setters
void ParticleSpring::SetParticleA(Particle* particle) {
    particleA = particle;
}

void ParticleSpring::SetFixedPoint(const Vector3f& point) {
    fixedPoint = point;
}

void ParticleSpring::SetRestLength(float length) {
    restLength = length;
}

void ParticleSpring::SetSpringConstant(float constant) {
    springConstant = constant;
}

void ParticleSpring::SetMaxStretch(float stretch) {
    maxStretch = stretch;
}

void ParticleSpring::SetIsElastic(bool elastic) {
    isElastic = elastic;
}