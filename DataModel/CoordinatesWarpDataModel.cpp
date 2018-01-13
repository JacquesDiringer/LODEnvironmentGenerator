#include "stdafx.h"
#include "CoordinatesWarpDataModel.h"
#include "CoordinatesWarpExpression.h"

using Math::CoordinatesWarpExpression;

namespace DataModel
{
	CoordinatesWarpDataModel::CoordinatesWarpDataModel()
	{
	}


	CoordinatesWarpDataModel::~CoordinatesWarpDataModel()
	{
	}

	FloatExpression * CoordinatesWarpDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		string currentLine;

		// Get the expression name.
		getline(*stream, currentLine);
		// Fetch the first expression in the previously read expressions.
		FloatExpression* xExpression = GetFloatExpressionByName(currentLine, previousExpressions);

		// Get the expression name.
		getline(*stream, currentLine);
		// Fetch the first expression in the previously read expressions.
		FloatExpression* yExpression = GetFloatExpressionByName(currentLine, previousExpressions);

		// Get the expression name.
		getline(*stream, currentLine);
		// Fetch the first expression in the previously read expressions.
		FloatExpression* zExpression = GetFloatExpressionByName(currentLine, previousExpressions);

		// Get the expression name.
		getline(*stream, currentLine);
		// Fetch the first expression in the previously read expressions.
		FloatExpression* childExpression = GetFloatExpressionByName(currentLine, previousExpressions);

		return new CoordinatesWarpExpression(xExpression, yExpression, zExpression, childExpression);
	}

	void CoordinatesWarpDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}

}