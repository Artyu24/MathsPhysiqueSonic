#pragma once
class Quaternion
{
public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);


private:
	float x;
    float y;
    float z;
    float w;
    
    //public static Quaternion operator *(Quaternion a, Quaternion b) = > Multiply(a, b);
    //
    //public static Vector3 operator *(Quaternion q, Vector3 v) = > RotationPointFromQuaternion(q, v);
    //
    //public Quaternion(float x, float y, float z, float w)
    //{
    //    this.x = x;
    //    this.y = y;
    //    this.z = z;
    //    this.w = w;
    //}
    //
    //public static Quaternion Identity{ get = > new Quaternion(0,0,0,1); }
    //
    //    public static Quaternion AngleAxis(float angle, Vector3 axis)
    //{
    //    axis = axis.Normalize();
    //
    //    Quaternion q = new Quaternion(
    //        axis.x * (float)Math.Sin(angle * MathUtils.DegToRad / 2),
    //        axis.y * (float)Math.Sin(angle * MathUtils.DegToRad / 2),
    //        axis.z * (float)Math.Sin(angle * MathUtils.DegToRad / 2),
    //        (float)Math.Cos(angle * MathUtils.DegToRad / 2));
    //
    //    return q;
    //}
    //
    //public Quaternion Normalize()
    //{
    //    float t = (float)Math.Sqrt(Math.Pow(w, 2) + Math.Pow(x, 2) + Math.Pow(y, 2) + Math.Pow(z, 2));
    //    return new Quaternion(x / t, y / t, z / t, w / t);
    //}
    //
    //private static Quaternion Multiply(Quaternion q1, Quaternion q2)
    //{
    //    return new Quaternion(
    //        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
    //        q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
    //        q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
    //        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
    //}
    //
    //private Quaternion Conjugaison(Quaternion q)
    //{
    //    return new Quaternion(q.w, -q.x, -q.y, -q.z);
    //}
};

