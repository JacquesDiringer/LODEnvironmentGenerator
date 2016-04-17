#include "stdafx.h"
#include "LevelFactoryDataModel.h"

#include <exception>

namespace DataModel
{
	LevelFactoryDataModel::LevelFactoryDataModel()
	{
	}

	LevelFactoryDataModel::~LevelFactoryDataModel()
	{
	}

	LevelFactory * LevelFactoryDataModel::Read(ifstream* stream, map<string, LevelFactory*>* previousFactories)
	{
		InternalRead(stream, previousFactories);

		// The InternalRead has to have read something.
		if (_name.length() > 0 && _factory != NULL)
		{
			if (previousFactories->find(_name) == previousFactories->end())
			{
				// The values read are stored in the factory map, with the name of the factory as the key.
				previousFactories->insert(std::pair<string, LevelFactory*>(_name, _factory));
			}
			else
			{
				throw new std::invalid_argument("This factory already exists.");
			}
		}
		else
		{
			// Otherwise, an exception is thrown.
			throw new std::invalid_argument("The factory has not been read correctly.");
		}

		return _factory;
	}

	void LevelFactoryDataModel::Write(ofstream* stream, LevelFactory* factoryToWrite)
	{
		InternalWrite(stream, factoryToWrite);
	}
}
