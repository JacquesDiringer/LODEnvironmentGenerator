#include "stdafx.h"
#include "LinearFunctionDataModel.h"
#include "LinearFunctionExpression.h"
#include "UtilityReaderWriter.h"
#include "Vector3.h"

using Math::LinearFunctionExpression;

namespace DataModel
{
	LinearFunctionDataModel::LinearFunctionDataModel()
	{
	}

	LinearFunctionDataModel::~LinearFunctionDataModel()
	{
	}

	FloatExpression * LinearFunctionDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		// Get the ratios Vector3.
		Math::Vector3 ratios = UtilityReaderWriter::ReadVector3(stream);

		return new LinearFunctionExpression(ratios);
	}

	void LinearFunctionDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}