#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	// Represents an origin centered cylinder.
	// At the center of the cylinder, value will be _radius.
	// It then linerealy decreases to 0 at the border.
	// Stays 0 out of the cylinder.
	class GENERATOR_API YCylinderExpression :
		public FloatExpression
	{
	public:
		YCylinderExpression(float radius, float height);
		virtual ~YCylinderExpression();

		/// Recursively evaluates the value of it's concrete FloatExpression implementations.
		float Evaluate(Vector3 coordinates);

	private:
		float _radius, _height;
	};
}

