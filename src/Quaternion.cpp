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

Vector3f Quaternion::RotateVector(Quaternion q, Vector3f& vec)
{
    Quaternion vecQuat(vec);
    Quaternion result = q * vecQuat * q.GetConjugaison();

    return result.GetVector();
}

float Quaternion::GetMagnitudeSquared()
{
    return pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2);
}

float Quaternion::GetMagnitude()
{
    return sqrt(GetMagnitudeSquared());
}

void Quaternion::Normalize()
{
    float norm = GetMagnitude();
    w /= norm;
    x /= norm;
    y /= norm;
    z /= norm;
}

float Quaternion::DotProduct(Quaternion b)
{
    return w * b.w + x * b.x + y * b.y + z * b.z;
}

Quaternion Quaternion::GetNormalize()
{
    float t = (float)sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));

    if (t == 0.f)
    {
        return Quaternion();
    }
    return Quaternion(w / t, x / t, y / t, z / t);
}

Quaternion Quaternion::GetConjugaison()
{
    return Quaternion(w, -x, -y, -z);
}

Vector3f Quaternion::GetVector() const
{
    return Vector3f(x, y, z);
}

Matrix Quaternion::GetRotationMatrix()
{
    Matrix rotation(3, 3, std::vector<float>{
        1 - 2 * (y * y + z * z), 2 * (x * y + z * w),     2 * (x * z - y * w),
        2 * (x * y - z * w)    , 1 - 2 * (x * x + z * z), 2 * (y * z + x * w),
        2 * (x * y + y * w)    , 2 * (y * z - x * w)    , 1 - 2 * (x * x + y * y)
    });
    return rotation;
}

Quaternion Quaternion::operator+(Quaternion b)
{
    return Quaternion(w + b.w, x + b.x, y + b.y, z + b.z);
}

Quaternion Quaternion::operator*(float scalar)
{
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
}
