#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	class GENERATOR_API LinearCombinationExpression :
		public FloatExpression
	{
	public:
		LinearCombinationExpression();
		LinearCombinationExpression(FloatExpression* expressionA, FloatExpression* expressionB, float ratioA, float ratioB);
		~LinearCombinationExpression();

		virtual float Evaluate(Vector3 coordinates);

	private:
		float _ratioA, _ratioB;
		FloatExpression* _expressionA;
		FloatExpression* _expressionB;
	};
}