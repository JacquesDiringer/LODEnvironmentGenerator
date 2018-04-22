#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	class GENERATOR_API ModuloExpression :
		public FloatExpression
	{
	public:
		ModuloExpression(FloatExpression* childExpression, int divider);
		~ModuloExpression();

		/// Recursively evaluates the value of it's concrete FloatExpression implementations.
		float Evaluate(Math::Vector3 coordinates);

	private:
		FloatExpression* _childExpression;
		int _divider;
	};

}
