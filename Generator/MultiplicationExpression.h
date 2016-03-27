#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	class GENERATOR_API MultiplicationExpression :
		public FloatExpression
	{
	public:
		MultiplicationExpression();
		MultiplicationExpression(FloatExpression* expression, float ratio);
		~MultiplicationExpression();

		virtual float Evaluate(Vector3 coordinates);

	private:
		float _ratio;
		FloatExpression* _expression;
	};


}