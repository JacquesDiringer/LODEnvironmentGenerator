#include "stdafx.h"
#include "ParametricPlane.h"


namespace Math
{
	ParametricPlane::ParametricPlane()
	{
		_normal = Vector3();
		_d = 0;
	}

	ParametricPlane::ParametricPlane(const Vector3 & normal, float d)
		: _normal(normal), _d(d)
	{
	}

	ParametricPlane::~ParametricPlane()
	{
	}

	bool ParametricPlane::PointOnNormalSide(const Vector3 & point) const
	{
		// The test will return true even if the point is on the plane itself.
		return Vector3::Dot((point - _normal * _d), _normal) >= 0;
	}

}