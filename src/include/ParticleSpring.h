#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleSpring : public IParticleForceGenerator
{
    public:
        ParticleSpring(Particle* particleA, const Vector3f& fixedPoint, float restLength, float springConstant, float maxStretch, bool isElastic = false);

        // Getters
        Particle* GetParticleA() const;
        const Vector3f& GetFixedPoint() const;
        float GetRestLength() const;
        float GetSpringConstant() const;
        float GetMaxStretch() const;
        bool GetIsElastic() const;

        // Setters
        void SetParticleA(Particle* particle);
        void SetFixedPoint(const Vector3f& point);
        void SetRestLength(float length);
        void SetSpringConstant(float constant);
        void SetMaxStretch(float stretch);
        void SetIsElastic(bool elastic);

    private:
        Particle* particleA;
        Vector3f fixedPoint;
        float restLength;
        float springConstant;
        float maxStretch;
        bool isElastic;
}

