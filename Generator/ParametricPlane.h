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
		ParametricPlane();
		ParametricPlane(const Vector3& normal, float d);
		~ParametricPlane();

		// Returns true if a point is on the same side of the plane than the normal, false otherwise.
		bool PointOnNormalSide(const Vector3& point) const;

		const Vector3& GetNormal() { return _normal; }
		
		float GetD() { return _d; }

	private:
		Vector3 _normal;
		float _d;
	};
}
