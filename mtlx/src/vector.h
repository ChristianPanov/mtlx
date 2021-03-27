#pragma once

struct vector3d
{
public:
	vector3d(float x, float y, float z);
	vector3d& operator+=(const vector3d& other);
	vector3d& operator-=(const vector3d& other);
	vector3d& operator*=(float scalar);
	vector3d& operator/=(float scalar);
	float x, y, z;
};