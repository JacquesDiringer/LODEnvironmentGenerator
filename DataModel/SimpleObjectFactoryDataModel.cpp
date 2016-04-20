#include "stdafx.h"
#include "SimpleObjectFactoryDataModel.h"
#include "SimpleObjectFactory.h"

using std::getline;
using Generator::SimpleObjectFactory;

namespace DataModel
{
	SimpleObjectFactoryDataModel::SimpleObjectFactoryDataModel()
	{
		_floatExpressions = new map<string, FloatExpression*>();
	}

	SimpleObjectFactoryDataModel::~SimpleObjectFactoryDataModel()
	{
	}

	LevelFactory * SimpleObjectFactoryDataModel::InternalRead(ifstream* stream, map<string, LevelFactory*>* previousFactories)
	{
		// Variables necessary for currently read factory initilization.
		string modelName;
		string textureName;
		float expansionDistance;

		// String containing the expansionDistance.
		string expansionDistanceString;
		// Name of the subLevelFactory to be read in the file.
		string subLevelFactoryName;

		// Get the model name line.
		getline(*stream, modelName);

		// Get the texture name line.
		getline(*stream, textureName);

		// Get the string distance of expansion of the factory.
		getline(*stream, expansionDistanceString);
		// Then translate it to a floating value.
		expansionDistance = std::stof(expansionDistanceString);

		// Get the string name of the sublevel factory.
		getline(*stream, subLevelFactoryName);

		// Get the sublevel factory according to its name, if it exist.
		LevelFactory* subLevelFactory = GetFactoryByName(subLevelFactoryName, previousFactories);

		// Set the factory to be stored in the map.
		_factory = new SimpleObjectFactory(modelName, textureName, expansionDistance, subLevelFactory);
		return _factory;
	}

	void SimpleObjectFactoryDataModel::InternalWrite(ofstream* stream, LevelFactory* factoryToWrite)
	{
	}
}