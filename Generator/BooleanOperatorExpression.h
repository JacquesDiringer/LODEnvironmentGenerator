#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	enum BooleanOperatorType
	{
		No,
		And,
		Or,
		Xor,
		Nand,
	};

	class GENERATOR_API BooleanOperatorExpression :
		public FloatExpression
	{
	public:
		BooleanOperatorExpression();
		BooleanOperatorExpression(FloatExpression* expressionA, FloatExpression* expressionB, BooleanOperatorType operatorType);
		~BooleanOperatorExpression();

		virtual float Evaluate(Vector3 coordinates);

	private:
		FloatExpression* _expressionA, * _expressionB;
		BooleanOperatorType _operatorType;
	};
}