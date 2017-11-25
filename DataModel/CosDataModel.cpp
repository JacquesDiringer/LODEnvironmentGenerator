#include "stdafx.h"
#include "CosDataModel.h"
#include "CosExpression.h"

using Math::CosExpression;


namespace DataModel
{
	CosDataModel::CosDataModel()
	{
	}

	CosDataModel::~CosDataModel()
	{
	}

	FloatExpression * CosDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		_expression = NULL;
		string currentLine;

		// Get the expression name.
		getline(*stream, currentLine);

		// Fetch the first expression in the previously read expressions.
		FloatExpression* expression = GetFloatExpressionByName(currentLine, previousExpressions);

		if (expression == NULL)
		{
			throw new std::invalid_argument("The expression has not been previously read.");
		}

		// Instanciate the linear combination expression and return it.
		return new CosExpression(expression);
	}

	void CosDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}