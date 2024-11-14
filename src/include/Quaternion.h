#pragma once

#include "Matrix.h"
#include <glm/glm.hpp>

class Quaternion
{
    public:
        Quaternion();
        Quaternion(float w, float x, float y, float z);
        Quaternion(Vector3f vec);

        float W() { return w; };
        float X() { return x; };
        float Y() { return y; };
        float Z() { return z; };

        static Quaternion Identity() { return Quaternion(1.f, 0, 0, 0); }
        static Quaternion GetRotationQuaternion(float angle, Vector3f axis);
        static Quaternion Multiply(Quaternion q1, Quaternion q2);
        
        void Normalize();
        float GetMagnitudeSquared();
        float GetMagnitude();
        float DotProduct(Quaternion b);
        Quaternion GetNormalize();
        Quaternion GetConjugaison();

        Matrix GetRotationMatrix();

        Quaternion operator+(Quaternion b);
        Quaternion operator*(Quaternion b) { return Multiply((*this), b); };
        Quaternion operator*(float scalar);

        operator glm::quat() const { return glm::quat(w, x, y, z); }

    private:
        float w;
	    float x;
        float y;
        float z;
};

//inline Quaternion operator*(Quaternion a, Quaternion b) { return Quaternion::Multiply(a, b); };

