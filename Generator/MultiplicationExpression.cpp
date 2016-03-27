#include "stdafx.h"
#include "MultiplicationExpression.h"


namespace Math
{
	MultiplicationExpression::MultiplicationExpression()
	{
	}

	MultiplicationExpression::MultiplicationExpression(FloatExpression * expression, float ratio)
		: _expression(expression), _ratio(ratio)
	{
	}


	MultiplicationExpression::~MultiplicationExpression()
	{
	}

	float MultiplicationExpression::Evaluate(Vector3 coordinates)
	{
		return _ratio * _expression->Evaluate(coordinates);
	}

}