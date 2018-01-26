#include "stdafx.h"
#include "ModuloDataModel.h"
#include "ModuloExpression.h"
#include "UtilityReaderWriter.h"

using Math::ModuloExpression;

namespace DataModel
{
	ModuloDataModel::ModuloDataModel()
	{
	}

	ModuloDataModel::~ModuloDataModel()
	{
	}

	FloatExpression * ModuloDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		string currentLine;
		// Get the expression name.
		getline(*stream, currentLine);

		// Fetch the first expression in the previously read expressions.
		FloatExpression* childExpression = GetFloatExpressionByName(currentLine, previousExpressions);

		// Get the divider float, that will be cast to an int.
		float divider = UtilityReaderWriter::ReadFloat(stream);

		return new ModuloExpression(childExpression, (int)divider);
	}

	void ModuloDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}

}