#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	class GENERATOR_API CosExpression :
		public FloatExpression
	{
	public:
		CosExpression();
		CosExpression(FloatExpression* expression);
		~CosExpression();

		virtual float Evaluate(Vector3 coordinates);

	private:
		FloatExpression* _expression;
	};


}