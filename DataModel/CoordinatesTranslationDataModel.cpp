#include "stdafx.h"
#include "CoordinatesTranslationDataModel.h"

#include "CoordinatesTranslationExpression.h"
#include "UtilityReaderWriter.h"

using Math::CoordinatesTranslationExpression;


namespace DataModel
{
	CoordinatesTranslationDataModel::CoordinatesTranslationDataModel()
	{
	}

	CoordinatesTranslationDataModel::~CoordinatesTranslationDataModel()
	{
	}

	FloatExpression * CoordinatesTranslationDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		// Read the translation first.
		Vector3 translation = UtilityReaderWriter::ReadVector3(stream);

		string currentLine;
		// Get the expression name.
		getline(*stream, currentLine);

		// Fetch the first expression in the previously read expressions.
		FloatExpression* childExpression = GetFloatExpressionByName(currentLine, previousExpressions);

		return new CoordinatesTranslationExpression(childExpression, translation);
	}

	void CoordinatesTranslationDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}
