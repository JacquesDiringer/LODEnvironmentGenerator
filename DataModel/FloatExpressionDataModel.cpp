#include "stdafx.h"
#include "FloatExpressionDataModel.h"


namespace DataModel
{
	FloatExpressionDataModel::FloatExpressionDataModel()
	{
	}


	FloatExpressionDataModel::~FloatExpressionDataModel()
	{
	}
	
	FloatExpression* FloatExpressionDataModel::Read(ifstream* stream, map<string, FloatExpression*>* previousExpressions)
	{
		// Set the name of the float expression, to be stored in the map.
		getline(*stream, _name);

		// Read the specific content of the float expression.
		// The concrete implementation is supposed to fill the _expression field.
		InternalRead(stream, previousExpressions);

		// The InternalRead has to have read something.
		if (_name.length() > 0 && _expression != NULL)
		{
			if (previousExpressions->find(_name) == previousExpressions->end())
			{
				// The values read are stored in the expressions map, with the name of the expression as the key.
				previousExpressions->insert(std::pair<string, FloatExpression*>(_name, _expression));
			}
			else
			{
				throw new std::invalid_argument("This float expression already exists.");
			}
		}
		else
		{
			// Otherwise, an exception is thrown.
			throw new std::invalid_argument("The float expression has not been read correctly.");
		}

		return _expression;
	}

	void FloatExpressionDataModel::Write(ofstream * stream, FloatExpression * expressionToWrite)
	{
	}

	Vector3 FloatExpressionDataModel::ReadVector3(ifstream* stream)
	{
		string currentLine;

		// Get the X component.
		getline(*stream, currentLine);
		float voxelSizeX = std::stof(currentLine);

		// Get the Y component.
		getline(*stream, currentLine);
		float voxelSizeY = std::stof(currentLine);

		// Get the Z component.
		getline(*stream, currentLine);
		float voxelSizeZ = std::stof(currentLine);

		// Combine them into the final Vector3.
		return Vector3(voxelSizeX, voxelSizeY, voxelSizeZ);
	}
}