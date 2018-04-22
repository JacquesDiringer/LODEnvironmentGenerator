#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	// Represents a coordinates warp for density functions.
	// The class will replace coordinates with the result of a float expression.
	class GENERATOR_API CoordinatesWarpExpression :
		public FloatExpression
	{
	public:
		CoordinatesWarpExpression(FloatExpression* xExpressionn, FloatExpression* yExpression, FloatExpression* zExpression, FloatExpression* childExpression);
		~CoordinatesWarpExpression();

		/// Recursively evaluates the value of it's concrete FloatExpression implementations.
		float Evaluate(Math::Vector3 coordinates);

	private:
		// Float expressions used to compute the new coordinates.
		FloatExpression* _xExpression;
		FloatExpression* _yExpression;
		FloatExpression* _zExpression;
		// Float expression that will use the new coordinates.
		FloatExpression* _childExpression;
	};

}
