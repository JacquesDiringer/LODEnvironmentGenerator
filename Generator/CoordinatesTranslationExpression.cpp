#include "stdafx.h"
#include "CoordinatesTranslationExpression.h"


namespace Math
{
	CoordinatesTranslationExpression::CoordinatesTranslationExpression(FloatExpression * childExpression, Vector3 translation)
		: _childExpression(childExpression), _translation(translation)
	{
	}

	CoordinatesTranslationExpression::~CoordinatesTranslationExpression()
	{
	}

	float CoordinatesTranslationExpression::Evaluate(Vector3 coordinates)
	{
		return _childExpression->Evaluate(coordinates + _translation);
	}

}