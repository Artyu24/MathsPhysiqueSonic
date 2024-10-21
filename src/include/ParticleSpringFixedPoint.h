#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"


class ParticleSpringFixedPoint : public IParticleForceGenerator
{
public:
    ParticleSpringFixedPoint(const Vector3f& fixedPoint, float restLength, float springConstant, float maxStretch, bool isElastic);

    void UpdateForce(std::shared_ptr<Particle> particle, float duration) override;
    // Getters
    const Vector3f& GetFixedPoint() const;
    float GetRestLength() const;
    float GetSpringConstant() const;
    float GetMaxStretch() const;
    bool GetIsElastic() const;

    // Setters
    void SetFixedPoint(const Vector3f& point);
    void SetRestLength(float length);
    void SetSpringConstant(float constant);
    void SetMaxStretch(float stretch);
    void SetIsElastic(bool elastic);


private:
    Vector3f fixedPoint;
    float restLength;
    float springConstant;
    float maxStretch;
    bool isElastic;
};

