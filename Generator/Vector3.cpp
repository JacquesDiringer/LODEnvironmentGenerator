#include "stdafx.h"
#include "Vector3.h"

#include <math.h>


namespace Math
{
	Vector3::Vector3()
	{
		_x = _y = _z = 0;
	}

	Vector3::Vector3(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}


	Vector3::~Vector3()
	{
	}

	float Vector3::Distance(Vector3 a, Vector3 b)
	{
		return sqrtf(
			pow(a.X() - b.X(), 2) +
			pow(a.Y() - b.Y(), 2) +
			pow(a.Z() - b.Z(), 2));
	}

	Vector3 Vector3::Add(Vector3 a, Vector3 b)
	{
		return Vector3(
			a.X() + b.X(),
			a.Y() + b.Y(),
			a.Z() + b.Z());
	}
}