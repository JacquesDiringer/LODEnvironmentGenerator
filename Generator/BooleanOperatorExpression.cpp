#include "stdafx.h"
#include "BooleanOperatorExpression.h"

#include <stdexcept>


namespace Math
{
	BooleanOperatorExpression::BooleanOperatorExpression()
	{
	}

	BooleanOperatorExpression::BooleanOperatorExpression(FloatExpression * expressionA, FloatExpression * expressionB, BooleanOperatorType operatorType)
		: _expressionA(expressionA), _expressionB(expressionB), _operatorType(operatorType)
	{
		// Void.
	}


	BooleanOperatorExpression::~BooleanOperatorExpression()
	{
	}

	float BooleanOperatorExpression::Evaluate(Vector3 coordinates)
	{
		// Expressions boolean values computation.
		bool result;
		bool aResult = _expressionA->Evaluate(coordinates) >= 1;
		bool bResult = false;
		if (_expressionB != NULL)
		{
			bResult = _expressionB->Evaluate(coordinates) >= 1;
		}

		switch (_operatorType)
		{
		case Math::No:
			result = !aResult;
			break;
		case Math::And:
			result = aResult && bResult;
			break;
		case Math::Or:
			result = aResult || bResult;
			break;
		case Math::Xor:
			result = (aResult || bResult) && !(aResult && bResult);
			break;
		case Math::Nand:
			result = !(aResult && bResult);
			break;
		default:
			throw new std::invalid_argument("Wrong enum.");
		}

		return result ? 1 : 0;
	}
}