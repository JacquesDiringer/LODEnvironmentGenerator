#include "stdafx.h"
#include "MultiplicationDataModel.h"

#include "MultiplicationExpression.h"
#include "UtilityReaderWriter.h"

using Math::MultiplicationExpression;


namespace DataModel
{
	MultiplicationDataModel::MultiplicationDataModel()
	{
	}

	MultiplicationDataModel::~MultiplicationDataModel()
	{
	}

	FloatExpression * MultiplicationDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		_expression = NULL;
		string currentLine;

		// Get the ratio.
		float ratio = UtilityReaderWriter::ReadFloat(stream);

		// Get the expression name.
		getline(*stream, currentLine);

		// Fetch the first expression in the previously read expressions.
		FloatExpression* expression = GetFloatExpressionByName(currentLine, previousExpressions);

		if (expression == NULL)
		{
			throw new std::invalid_argument("The expression has not been previously read.");
		}

		// Instanciate the linear combination expression and return it.
		return new MultiplicationExpression(expression, ratio);
	}

	void MultiplicationDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}