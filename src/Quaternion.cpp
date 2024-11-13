#include "include/Quaternion.h"

Quaternion::Quaternion() : w(0), x(0), y(0), z(0)
{
}

Quaternion::Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z)
{
}

Quaternion::Quaternion(Vector3f vec) : w(0), x(vec.x), y(vec.y), z(vec.z)
{
}

Quaternion Quaternion::GetRotationQuaternion(float angle, Vector3f axis)
{
    axis = axis.Normalize();

    Quaternion q = Quaternion(
        (float)cos(angle * DEG_TO_RAD / 2),
        axis.x * (float)sin(angle * DEG_TO_RAD / 2),
        axis.y * (float)sin(angle * DEG_TO_RAD / 2),
        axis.z * (float)sin(angle * DEG_TO_RAD / 2));

    return q;
}

Quaternion Quaternion::Multiply(Quaternion q1, Quaternion q2)
{
    return Quaternion(
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
        q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w);
}

float Quaternion::GetMagnitudeSquared()
{
    return 0.0f;
}

float Quaternion::GetMagnitude()
{
    return 0.0f;
}

void Quaternion::Normalize()
{
}

Quaternion Quaternion::GetNormalize()
{
    float t = (float)sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
    return Quaternion(w / t, x / t, y / t, z / t);
}

Quaternion Quaternion::Conjugaison(Quaternion q)
{
    return Quaternion(q.w, -q.x, -q.y, -q.z);
}
