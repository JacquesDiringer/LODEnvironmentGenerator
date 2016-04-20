#include "stdafx.h"
#include "TransformationFactoryDataModel.h"

#include "TransformationFactory.h"

using std::getline;
using Generator::TransformationFactory;


namespace DataModel
{
	TransformationFactoryDataModel::TransformationFactoryDataModel()
	{
		_floatExpressions = new map<string, FloatExpression*>();
	}

	TransformationFactoryDataModel::~TransformationFactoryDataModel()
	{
	}

	LevelFactory * TransformationFactoryDataModel::InternalRead(ifstream * stream, map<string, LevelFactory*>* previousFactories)
	{
		// Name of the subLevelFactory to be read in the file.
		string subLevelFactoryName;
		// Get the string name of the sublevel factory.
		getline(*stream, subLevelFactoryName);
		// Get the sublevel factory according to its name, if it exist.
		LevelFactory* subLevelFactory = GetFactoryByName(subLevelFactoryName, previousFactories);

		// The sublevel has to exist.
		if (subLevelFactory == NULL)
		{
			throw new std::invalid_argument("A transformation factory should always have a sublevel.");
		}

		// Read the 16 matrix values.
		float matrixParameters[16];
		string currentParameter;

		for (int i = 0; i < 16; i++)
		{
			getline(*stream, currentParameter);
			matrixParameters[i] = std::stof(currentParameter);
		}

		// Create the matrix.
		Matrix4 transformation = Matrix4(	matrixParameters[0], matrixParameters[1], matrixParameters[2], matrixParameters[3],
									matrixParameters[4], matrixParameters[5], matrixParameters[6], matrixParameters[7],
									matrixParameters[8], matrixParameters[9], matrixParameters[10], matrixParameters[11],
									matrixParameters[12], matrixParameters[13], matrixParameters[14], matrixParameters[15]);

		_factory = new TransformationFactory(subLevelFactory, transformation);
		return _factory;
	}

	void TransformationFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
	}
}