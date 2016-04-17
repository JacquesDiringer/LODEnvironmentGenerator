#include "stdafx.h"
#include "SimpleObjectFactoryDataModel.h"
#include "SimpleObjectFactory.h"

using std::getline;
using Generator::SimpleObjectFactory;

namespace DataModel
{
	SimpleObjectFactoryDataModel::SimpleObjectFactoryDataModel()
	{
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
		LevelFactory* subLevelFactory = NULL;

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

		// If this factory is supposed to have a child.
		if (subLevelFactoryName != "NULL")
		{
			// Then look if this factory has been previously loaded.
			map<string, LevelFactory*>::iterator factoryIt = previousFactories->find(subLevelFactoryName);
			if (factoryIt == previousFactories->end())
			{
				throw new std::invalid_argument("Children factory not previously read.");
			}

			// Register the found factory as the sublevel of future factory.
			subLevelFactory = (*factoryIt).second;
		}

		// Set the factory to be stored in the map.
		_factory = new SimpleObjectFactory(modelName, textureName, expansionDistance, subLevelFactory);
		return _factory;
	}

	void SimpleObjectFactoryDataModel::InternalWrite(ofstream* stream, LevelFactory* factoryToWrite)
	{
	}
}