#include "stdafx.h"
#include "LevelFactoryDataModel.h"

#include <exception>
#include <iostream>


namespace DataModel
{
	LevelFactoryDataModel::LevelFactoryDataModel()
	{
		_floatExpressions = new map<string, FloatExpression*>();
	}

	LevelFactoryDataModel::~LevelFactoryDataModel()
	{
	}

	LevelFactory * LevelFactoryDataModel::Read(ifstream* stream, map<string, LevelFactory*>* previousFactories)
	{
		// Set the name of the factory, to be stored in the map.
		getline(*stream, _name);

		// Read the specific content of the factory.
		_factory = InternalRead(stream, previousFactories);

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
				throw new std::invalid_argument("This factory already exists : " + _name);
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

	void LevelFactoryDataModel::AddFloatExpression(string name, FloatExpression* expression)
	{
		_floatExpressions->insert(std::pair<string, FloatExpression*>(name, expression));
	}

	void LevelFactoryDataModel::AddFloatExpression(map<string, FloatExpression*>* additionalMap)
	{
		_floatExpressions->insert(additionalMap->begin(), additionalMap->end());
	}

	LevelFactory * LevelFactoryDataModel::GetFactoryByName(string name, map<string, LevelFactory*>* previousFactories)
	{
		// If this factory is supposed to have a child.
		if (name != "NULL")
		{
			// Then look if this factory has been previously loaded.
			map<string, LevelFactory*>::iterator factoryIt = previousFactories->find(name);
			if (factoryIt == previousFactories->end())
			{
				std::cout << "Erroc : children factory not previously read : " << name;
				throw new std::invalid_argument("Children factory not previously read.");
			}

			// Register the found factory as the sublevel of future factory.
			return (*factoryIt).second;
		}

		return NULL;
	}
}
