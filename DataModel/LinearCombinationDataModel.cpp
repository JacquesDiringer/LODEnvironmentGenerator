#include "stdafx.h"
#include "LinearCombinationDataModel.h"

#include "LinearCombinationExpression.h"
#include "UtilityReaderWriter.h"

using std::getline;

using Math::LinearCombinationExpression;

namespace DataModel
{
	LinearCombinationDataModel::LinearCombinationDataModel()
	{
	}

	LinearCombinationDataModel::~LinearCombinationDataModel()
	{
	}

	FloatExpression * LinearCombinationDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		_expression = NULL;
		string currentLine;

		// Get the first ratio.
		float aRatio = UtilityReaderWriter::ReadFloat(stream);

		// Get the first expression name.
		getline(*stream, currentLine);

		// Fetch the first expression in the previously read expressions.
		FloatExpression* aExpression = GetFloatExpressionByName(currentLine, previousExpressions);


		// Get the second ratio.
		float bRatio = UtilityReaderWriter::ReadFloat(stream);

		// Get the second expression name.
		getline(*stream, currentLine);

		// Fetch the second expression in the previously read expressions.
		FloatExpression* bExpression = GetFloatExpressionByName(currentLine, previousExpressions);

		if (aExpression == NULL || bExpression == NULL)
		{
			throw new std::invalid_argument("One of the necessary expression has not been previously read.");
		}

		// Instanciate the linear combination expression and return it.
		return new LinearCombinationExpression(aExpression, bExpression, aRatio, bRatio);
	}

	void LinearCombinationDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}