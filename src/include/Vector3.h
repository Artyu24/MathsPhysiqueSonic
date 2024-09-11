#pragma once

#include <cmath>
#include <glm/glm.hpp>

template<typename T>
struct Vector3
{
	T x, y, z;

	Vector3() = default;
	explicit Vector3(T V) :
	x(V),
	y(V),
	z(V)
	{
	}

	Vector3(T X, T Y, T Z) :
		x(X), y(Y), z(Z)
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

	float Length();
	float SquaredLength();
	Vector3 Normalize();
	float DotProduct(Vector3 v);
	Vector3 CrossProduct(Vector3 v);

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

template <typename T>
float Vector3<T>::Length()
{
	return sqrt(pow(x) + pow(y) + pow(z));
}

template<typename T>
float Vector3<T>::SquaredLength()
{
	return pow(x) + pow(y) + pow(z);
}

template <typename T>
Vector3<T> Vector3<T>::Normalize()
{
	float invMagnitude = 1 / Magnitude();
	return Vector3(x * invMagnitude, y * invMagnitude, z * invMagnitude);
}

template<typename T>
inline float Vector3<T>::DotProduct(Vector3 v)
{
	return x * v.x + y * v.y + z * v.z;
}

template<typename T>
inline Vector3<T> Vector3<T>::CrossProduct(Vector3 v)
{
	return Vector3(

		y*v.z - z * v.y,
		z*v.x - x*v.z,
		x*v.y - y*v.x
	);
}
