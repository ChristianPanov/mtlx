#pragma once

struct vector3d
{
public:
	vector3d(float x, float y, float z);

public:
	float& operator[](unsigned int index);
	const float& operator[](unsigned int index) const;

public:
	vector3d& operator+=(const vector3d& other);
	vector3d& operator-=(const vector3d& other);
	vector3d& operator*=(float scalar);
	vector3d& operator/=(float scalar);

public:
	float x, y, z;
};