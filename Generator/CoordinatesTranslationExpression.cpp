#include "stdafx.h"
#include "CoordinatesTranslationExpression.h"


namespace Math
{
	CoordinatesTranslationExpression::CoordinatesTranslationExpression(FloatExpression * childExpression, Math::Vector3 translation)
		: _childExpression(childExpression), _translation(translation)
	{
	}

	CoordinatesTranslationExpression::~CoordinatesTranslationExpression()
	{
	}

	float CoordinatesTranslationExpression::Evaluate(Math::Vector3 coordinates)
	{
		return _childExpression->Evaluate(coordinates + _translation);
	}

}