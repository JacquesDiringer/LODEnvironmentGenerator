#include "stdafx.h"
#include "SimpleObjectFactoryDataModel.h"

#include "SimpleObjectFactory.h"
#include "UtilityReaderWriter.h"

using std::getline;
using Generator::SimpleObjectFactory;

namespace DataModel
{
	SimpleObjectFactoryDataModel::SimpleObjectFactoryDataModel()
	{
		_floatExpressions = new unordered_map<string, FloatExpression*>();
	}

	SimpleObjectFactoryDataModel::~SimpleObjectFactoryDataModel()
	{
	}

	LevelFactory * SimpleObjectFactoryDataModel::InternalRead(ifstream* stream, unordered_map<string, LevelFactory*>* previousFactories)
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

		// Get the float distance of expansion of the factory.
		expansionDistance = UtilityReaderWriter::ReadFloat(stream);

		// Get the string name of the sublevel factory.
		getline(*stream, subLevelFactoryName);

		// Get the sublevel factory according to its name, if it exist.
		LevelFactory* subLevelFactory = GetFactoryByName(subLevelFactoryName, previousFactories);

		// Return the factory to be stored in the map.
		return new SimpleObjectFactory(modelName, textureName, expansionDistance, subLevelFactory);
	}

	void SimpleObjectFactoryDataModel::InternalWrite(ofstream* stream, LevelFactory* factoryToWrite)
	{
		throw std::exception("Not implemented");
	}
}