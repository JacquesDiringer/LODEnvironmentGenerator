#include "stdafx.h"
#include "DependenceTreeDataModel.h"

#include "SimpleObjectFactoryDataModel.h"
#include "ComplexObjectFactoryDataModel.h"
#include "TransformationFactoryDataModel.h"

#include<iostream>

namespace DataModel
{
	DependenceTreeDataModel::DependenceTreeDataModel()
	{
		_factoriesDataModelMap = map<string, LevelFactoryDataModel*>();
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("SimpleObjectFactory", new SimpleObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("ComplexObjectFactory", new ComplexObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("TransformationFactory", new TransformationFactoryDataModel));
	}


	DependenceTreeDataModel::~DependenceTreeDataModel()
	{
	}

	LevelFactory * DependenceTreeDataModel::Read(string filePath)
	{
		// A map of the the factories that have already been read, stored by name.
		// This is done for children dependencies purposes.
		map<string, LevelFactory*>* previousFactories = new map<string, LevelFactory*>();

		// Last factory that has been read, it will be returned to define the root factory.
		LevelFactory* lastFactory;

		// Open an input stream to the designated file path.
		ifstream inputStream(filePath, ifstream::in);

		// If the input stream has correctly been opened.
		if (inputStream)
		{
			string currentLine;

			// Get lines until the end of the file.
			while (std::getline(inputStream, currentLine))
			{
				// Lines can be empty between factories for easier human reading purposes.
				if (currentLine.length() > 0)
				{
					// Search for the right data model to read the factory.
					map<string, LevelFactoryDataModel*>::iterator factoryReaderIt = _factoriesDataModelMap.find(currentLine);
					if (factoryReaderIt == _factoriesDataModelMap.end())
					{
						throw new std::invalid_argument("There is no data model able to read that kind of factory.");
					}

					// Retrieve the data model.
					LevelFactoryDataModel* factoryReader = (*factoryReaderIt).second;
					// Do the reading.
					lastFactory = factoryReader->Read(&inputStream, previousFactories);
				}
			}
		}
		else
		{
			throw new std::invalid_argument("File not found.");
		}

		// Return the last factory read, it will become the root factory.
		return lastFactory;
	}

}