#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"


class ParticleSpring : public IParticleForceGenerator
{
public:
    ParticleSpring(std::shared_ptr<Particle> particleA, float restLength, float springConstant, float maxStretch, bool isElastic = false);

    void UpdateForce(std::shared_ptr<Particle> particle, float duration) override;
    // Getters
    std::shared_ptr<Particle> GetParticleA() const;
    float GetRestLength() const;
    float GetSpringConstant() const;
    float GetMaxStretch() const;
    bool GetIsElastic() const;

    // Setters
    void SetParticleA(std::shared_ptr<Particle> particle);
    void SetRestLength(float length);
    void SetSpringConstant(float constant);
    void SetMaxStretch(float stretch);
    void SetIsElastic(bool elastic);
    

private:
    std::shared_ptr<Particle> particleA;
    float restLength;
    float springConstant;
    float maxStretch;
    bool isElastic;
};

