#include "vector.h"

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
