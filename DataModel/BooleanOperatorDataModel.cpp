#include "stdafx.h"
#include "BooleanOperatorDataModel.h"
#include "BooleanOperatorExpression.h"

#include<algorithm>

using Math::BooleanOperatorExpression;

namespace DataModel
{
	BooleanOperatorDataModel::BooleanOperatorDataModel()
	{
	}


	BooleanOperatorDataModel::~BooleanOperatorDataModel()
	{
	}
	FloatExpression * BooleanOperatorDataModel::InternalRead(ifstream * stream, map<string, FloatExpression*>* previousExpressions)
	{
		string currentLine;

		// Read the first line, should be the operator type.
		getline(*stream, currentLine);
		// Convert the line to upper case to avoid case issues.
		std::transform(currentLine.begin(), currentLine.end(), currentLine.begin(), ::toupper);

		Math::BooleanOperatorType operatorType;

		if (currentLine == "NO")
		{
			operatorType = Math::BooleanOperatorType::No;
		}
		else if (currentLine == "AND")
		{
			operatorType = Math::BooleanOperatorType::And;
		}
		else if (currentLine == "OR")
		{
			operatorType = Math::BooleanOperatorType::Or;
		}
		else if (currentLine == "XOR")
		{
			operatorType = Math::BooleanOperatorType::Xor;
		}
		else if (currentLine == "NAND")
		{
			operatorType = Math::BooleanOperatorType::Nand;
		}
		else
		{
			throw new std::invalid_argument("Wrong enum.");
		}

		// Read the sub expressions.

		// Get the expression A name.
		getline(*stream, currentLine);

		// Fetch the first expression in the previously read expressions.
		FloatExpression* expressionA = GetFloatExpressionByName(currentLine, previousExpressions);

		if (expressionA == NULL)
		{
			throw new std::invalid_argument("The expression has not been previously read.");
		}

		// Get the expression B name.
		getline(*stream, currentLine);

		// Fetch the first expression in the previously read expressions.
		FloatExpression* expressionB = NULL;
		
		if (currentLine != "NULL")
		{
			expressionB = GetFloatExpressionByName(currentLine, previousExpressions);

			if (expressionB == NULL)
			{
				throw new std::invalid_argument("The expression has not been previously read.");
			}
		}


		return new BooleanOperatorExpression(expressionA, expressionB, operatorType);
	}

	void BooleanOperatorDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}