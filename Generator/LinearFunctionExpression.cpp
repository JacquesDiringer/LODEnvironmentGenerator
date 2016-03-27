#include "stdafx.h"
#include "LinearFunctionExpression.h"


namespace Math
{
	LinearFunctionExpression::LinearFunctionExpression()
	{
	}

	LinearFunctionExpression::LinearFunctionExpression(Vector3 ratios)
		: _ratios(ratios)
	{
	}


	LinearFunctionExpression::~LinearFunctionExpression()
	{
	}

	float LinearFunctionExpression::Evaluate(Vector3 coordinates)
	{
		Vector3 multiplication = coordinates * _ratios;
		return multiplication.X() + multiplication.Y() + multiplication.Z();
	}

}