#pragma once
#include "Vector3.h"

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

    static Quaternion Identity() { return Quaternion(0,0,0,1); }
    static Quaternion RotateAround(float angle, Vector3f axis);
    static Quaternion Multiply(Quaternion q1, Quaternion q2);
    Quaternion Normalize();
    Quaternion Conjugaison(Quaternion q);

private:
    float w;
	float x;
    float y;
    float z;
};

inline Quaternion operator*(Quaternion a, Quaternion b) { return Quaternion::Multiply(a, b); };
