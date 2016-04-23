#include "stdafx.h"
#include "LinearFunctionDataModel.h"
#include "LinearFunctionExpression.h"
#include "Vector3.h"

using Math::LinearFunctionExpression;
using Math::Vector3;

namespace DataModel
{
	LinearFunctionDataModel::LinearFunctionDataModel()
	{
	}

	LinearFunctionDataModel::~LinearFunctionDataModel()
	{
	}

	FloatExpression * LinearFunctionDataModel::InternalRead(ifstream * stream, map<string, FloatExpression*>* previousExpressions)
	{
		// Get the ratios Vector3.
		Vector3 ratios = ReadVector3(stream);
		
		_expression = new LinearFunctionExpression(ratios);

		return _expression;
	}

	void LinearFunctionDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}