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

	float Vector3::Distance(const Vector3 a, const Vector3 b)
	{
		return sqrtf(
			pow(a.X() - b.X(), 2) +
			pow(a.Y() - b.Y(), 2) +
			pow(a.Z() - b.Z(), 2));
	}

	Vector3 Vector3::Add(const Vector3 a, const Vector3 b)
	{
		return Vector3(
			a.X() + b.X(),
			a.Y() + b.Y(),
			a.Z() + b.Z());
	}

	float Vector3::Length() const
	{
		return Vector3::Distance(*this, Vector3());
	}

	Vector3 Vector3::operator+(const Vector3 b)
	{
		return Vector3(
			X() + b.X(),
			Y() + b.Y(),
			Z() + b.Z());
	}

	Vector3 Vector3::Multiply(const Vector3 a, const Vector3 b)
	{
		return Vector3(
			a.X() * b.X(),
			a.Y() * b.Y(),
			a.Z() * b.Z());
	}

	Vector3 Vector3::operator*(const Vector3 b)
	{
		return Vector3(
			X() * b.X(),
			Y() * b.Y(),
			Z() * b.Z());
	}

	Vector3 Vector3::operator*(const float multiplier)
	{
		return Vector3(
			X() * multiplier,
			Y() * multiplier,
			Z() * multiplier);
	}

	bool Vector3::operator==(const Vector3 other)
	{
		return _x == other.X() && _y == other.Y() && _z == other.Z();
	}

	bool Vector3::operator<(const Vector3 other) const
	{
		if (_x != other.X())
		{
			return _x < other.X();
		}

		if (_y != other.Y())
		{
			return _y < other.Y();
		}

		return _z < other.Z();
	}
}