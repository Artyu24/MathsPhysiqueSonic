#pragma once
#include "Vector3.h"

class Quaternion
{
public:
    Quaternion();
    Quaternion(float w, float x, float y, float z);
    Quaternion(Vector3f vec);

    static Quaternion Identity() { return Quaternion(0,0,0,1); }
    static Quaternion AngleAxis(float angle, Vector3f axis);
    static Quaternion Multiply(Quaternion q1, Quaternion q2);
    Quaternion Normalize();
    Quaternion Conjugaison(Quaternion q);

    Quaternion operator*(Quaternion a, Quaternion b) { return Multiply(a, b); };
private:
    float w;
	float x;
    float y;
    float z;
};

