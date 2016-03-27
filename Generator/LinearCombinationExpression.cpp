#include "stdafx.h"
#include "LinearCombinationExpression.h"

namespace Math
{
	LinearCombinationExpression::LinearCombinationExpression()
	{
	}

	LinearCombinationExpression::LinearCombinationExpression(FloatExpression * expressionA, FloatExpression * expressionB, float ratioA, float ratioB)
		: _expressionA(expressionA), _expressionB(expressionB), _ratioA(ratioA), _ratioB(ratioB)
	{
	}


	LinearCombinationExpression::~LinearCombinationExpression()
	{
	}

	float LinearCombinationExpression::Evaluate(Vector3 coordinates)
	{
		return _ratioA * _expressionA->Evaluate(coordinates) + _ratioB * _expressionB->Evaluate(coordinates);
	}

}