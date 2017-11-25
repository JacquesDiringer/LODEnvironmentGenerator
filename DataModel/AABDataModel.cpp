#include "stdafx.h"
#include "AABDataModel.h"
#include "UtilityReaderWriter.h"
#include "AABExpression.h"

using Math::AABExpression;

namespace DataModel
{
	AABDataModel::AABDataModel()
	{
	}


	AABDataModel::~AABDataModel()
	{
	}

	FloatExpression * AABDataModel::InternalRead(ifstream * stream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		Vector3 boxOrigin = UtilityReaderWriter::ReadVector3(stream);
		Vector3 boxDimensions = UtilityReaderWriter::ReadVector3(stream);
		bool centered = UtilityReaderWriter::ReadBool(stream);

		// Instanciate the AABExpression and return it.
		return new AABExpression(boxOrigin, boxDimensions, centered);
	}

	void AABDataModel::InternalWrite(ofstream * stream, FloatExpression * expressionToWrite)
	{
		throw std::exception("Not implemented");
	}
}