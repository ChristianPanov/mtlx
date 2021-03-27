#include "vector.h"

#include <cmath>

vector3d::vector3d(float x, float y, float z)
	: x{ x }, y{ y }, z{ z }
{}

float& vector3d::operator[](unsigned int index)
{
	return (&x)[index];
}

const float& vector3d::operator[](unsigned int index) const
{
	return (&x)[index];
}

vector3d& vector3d::operator+=(const vector3d& other)
{
	x += other.x;
	y += other.y;
	z += other.y;
	return *this;
}

vector3d& vector3d::operator-=(const vector3d& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.y;
	return *this;
}

vector3d& vector3d::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

vector3d& vector3d::operator/=(float scalar)
{
	scalar = 1.0f / scalar;
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

float magnitude(const vector3d& vec)
{
	return (std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

vector3d normalize(const vector3d& vec)
{
	return (vec / magnitude(vec));
}

vector3d operator+(const vector3d& vec1, const vector3d& vec2)
{
	return vector3d(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

vector3d operator-(const vector3d& vec1, const vector3d& vec2)
{
	return vector3d(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

vector3d operator*(const vector3d& vec, float scalar)
{
	return vector3d(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

vector3d operator/(const vector3d& vec, float scalar)
{
	scalar = 1.0f / scalar;
	return vector3d(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}
