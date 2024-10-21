
#include "include/ParticleSpring.h"
#include "ofMain.h"

ParticleSpring::ParticleSpring(Particle* particleA, float restLength, float springConstant, float maxStretch, bool isElastic)
    : particleA(particleA), 
    restLength(restLength),
    springConstant(springConstant),
    maxStretch(maxStretch),
    isElastic(isElastic)
{
}


void ParticleSpring::UpdateForce(std::shared_ptr<Particle> particle, float duration)
{
    Vector3<float> forceDirection;
    
    forceDirection = particle->GetPosition() - particleA->GetPosition();
    

    float length = forceDirection.Length();
    float deltaLength = length - restLength;

    if (isElastic && length > maxStretch) {
        length = maxStretch;  
    }
   
    // Loi de Hooke : F = -k * deltaX
    Vector3<float> force = forceDirection.Normalize() * (-springConstant * deltaLength);

    particle->AddForce(force);
    particleA->AddForce(-force);
   
}

// Getters
Particle* ParticleSpring::GetParticleA() const {
    return particleA;
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

