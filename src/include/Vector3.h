#pragma once

#include <cmath>
#include <glm/glm.hpp>

template<typename T>
struct Vector3
{
	T x;
	T y;
	T z;

	Vector3() :
		x(T{}), y(T{}), z(T{})
	{
	}
	Vector3(T x, T y, T z) :
		x(x), y(y), z(z)
	{
	}
	Vector3(glm::vec3 vec) :
		x(vec.x), y(vec.y), z(vec.z)
	{
	}

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;
	Vector3 operator/(const Vector3& other) const;
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const Vector3& other);
	Vector3& operator/=(const Vector3& other);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3 operator+(const T& other) const;
	Vector3 operator-(const T& other) const;
	Vector3 operator*(const T& other) const;
	Vector3 operator/(const T& other) const;
	Vector3& operator+=(const T& other);
	Vector3& operator-=(const T& other);
	Vector3& operator*=(const T& other);
	Vector3& operator/=(const T& other);

	Vector3 operator-() const;

	operator glm::vec3() { return glm::vec3(x, y, z); }

	//Vector3& Rotate(const float& angle);
	//static Vector3 Rotate(const Vector3& vec, float angle);

	//float Magnitude();
	//Vector3 Normalize();

	/*std::string ToString() const
	{
		return std::format("({},{})\n", x, y);
	}*/

};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;

template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3& other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3& other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(const Vector3& other) const
{
	return Vector3(x * other.x, y * other.y, z * other.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator/(const Vector3& other) const
{
	return Vector3(x / other.x, y / other.y, z / other.z);
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;

	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const Vector3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;

	return *this;
}

template<typename T>
bool Vector3<T>::operator==(const Vector3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

template<typename T>
bool Vector3<T>::operator!=(const Vector3& other) const
{
	return x != other.x || y != other.y || z != other.z;
}

template<typename T>
inline Vector3<T> Vector3<T>::operator+(const T& other) const
{
	return Vector3(x + other, y + other, z + other);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-(const T& other) const
{
	return Vector3(x - other, y - other, z - other);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(const T& other) const
{
	return Vector3(x * other, y * other, z * other);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator/(const T& other) const
{
	return Vector3(x / other, y / other, z / other);
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const T& other)
{
	x += other;
	y += other;
	z += other;

	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(const T& other)
{
	x -= other;
	y -= other;
	z -= other;

	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const T& other)
{
	x *= other;
	y *= other;
	z *= other;

	return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const T& other)
{
	x /= other;
	y /= other;
	z /= other;

	return *this;
}

template <typename T>
Vector3<T> Vector3<T>::operator-() const
{
	return Vector3(x * -1, y * -1, z * -1);
}

//template <typename T>
//inline Vector3<T>& Vector3<T>::Rotate(const float& angle)
//{
//	float rad = DEG2RAD(angle);
//	float tempX = x * cos(rad) - y * sin(rad);
//	float tempY = x * sin(rad) + y * cos(rad);
//
//	x = tempX;
//	y = tempY;
//
//	return *this;
//}
//template <typename T>
//Vector3<T> Vector3<T>::Rotate(const Vector3& vec, float angle)
//{
//	Vector3 rotatedVec = vec;
//	return rotatedVec.Rotate(angle);
//}
//
//template <typename T>
//float Vector3<T>::Magnitude()
//{
//	return sqrt(pow(x) + pow(y));
//}
//
//template <typename T>
//Vector3<T> Vector3<T>::Normalize()
//{
//	return Vector3(x / Magnitude(), y / Magnitude());
//}