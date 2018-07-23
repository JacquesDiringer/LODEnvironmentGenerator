#pragma once

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

#include "Vector3.h"

using Math::Vector3;

namespace Math
{
	class GENERATOR_API ParametricPlane
	{
	public:
		ParametricPlane(const Vector3& normal, float d);
		~ParametricPlane();

		// Return true if a point is on the same side of the plane than the normal, false otherwise.
		bool PointOnNormalSide(const Vector3& point) const;

	private:
		Vector3 _normal;
		float _d;
	};
}
