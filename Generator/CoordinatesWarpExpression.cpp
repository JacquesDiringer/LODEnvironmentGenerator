#include "stdafx.h"
#include "CoordinatesWarpExpression.h"


namespace Math
{
	CoordinatesWarpExpression::CoordinatesWarpExpression(FloatExpression* xExpressionn, FloatExpression* yExpression, FloatExpression* zExpression, FloatExpression* childExpression)
		: _xExpression(xExpressionn), _yExpression(yExpression), _zExpression(zExpression), _childExpression(childExpression)
	{
	}


	CoordinatesWarpExpression::~CoordinatesWarpExpression()
	{
	}

	float CoordinatesWarpExpression::Evaluate(Math::Vector3 coordinates)
	{
		// Compute the new coordinates.
		Math::Vector3 newCoordinates = Math::Vector3(_xExpression->Evaluate(coordinates), _yExpression->Evaluate(coordinates), _zExpression->Evaluate(coordinates));
		// Use them to calculate the child expression.
		return _childExpression->Evaluate(newCoordinates);
	}

}