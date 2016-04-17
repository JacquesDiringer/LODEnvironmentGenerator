#include "stdafx.h"
#include "SimpleObjectFactoryDataModel.h"

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

		// Set the name of the factory, to be stored in the map.
		getline(*stream, _name);

		getline(*stream, modelName);

		getline(*stream, textureName);

		getline(*stream, expansionDistanceString);
		expansionDistance = std::stof(expansionDistanceString);

		getline(*stream, subLevelFactoryName);
		map<string, LevelFactory*>::iterator factoryIt = previousFactories->find(subLevelFactoryName);
		if (subLevelFactoryName != "NULL")
		{
			if (factoryIt == previousFactories->end())
			{
				throw new std::invalid_argument("Children factory not previously read.");
			}
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