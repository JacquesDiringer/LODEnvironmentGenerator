#include "stdafx.h"
#include "ModuloExpression.h"


namespace Math
{
	ModuloExpression::ModuloExpression(FloatExpression* childExpression, int divider)
		: _childExpression(childExpression), _divider(divider)
	{
	}


	ModuloExpression::~ModuloExpression()
	{
	}
	
	float ModuloExpression::Evaluate(Vector3 coordinates)
	{
		return std::abs((int)_childExpression->Evaluate(coordinates)) % _divider;
	}

}