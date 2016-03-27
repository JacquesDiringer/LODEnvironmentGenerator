#include "stdafx.h"
#include "CosExpression.h"

#include<cmath>

namespace Math
{
	CosExpression::CosExpression()
	{
	}

	CosExpression::CosExpression(FloatExpression * expression)
		: _expression(expression)
	{
	}


	CosExpression::~CosExpression()
	{
	}

	float CosExpression::Evaluate(Vector3 coordinates)
	{
		return std::cos(_expression->Evaluate(coordinates));
	}

}