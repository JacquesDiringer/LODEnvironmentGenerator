#include "stdafx.h"
#include "YCylinderDataModel.h"
#include "UtilityReaderWriter.h"
#include "YCylinderExpression.h"

using Math::YCylinderExpression;

namespace DataModel
{
	YCylinderDataModel::YCylinderDataModel()
	{
	}


	YCylinderDataModel::~YCylinderDataModel()
	{
	}

	FloatExpression * YCylinderDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		float radius = UtilityReaderWriter::ReadFloat(stream);
		float height = UtilityReaderWriter::ReadFloat(stream);

		return new YCylinderExpression(radius, height);
	}

	void YCylinderDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}

}