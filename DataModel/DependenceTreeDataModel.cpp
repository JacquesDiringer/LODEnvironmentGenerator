#include "stdafx.h"
#include "DependenceTreeDataModel.h"

#include "SimpleObjectFactoryDataModel.h"
#include "ComplexObjectFactoryDataModel.h"
#include "TransformationFactoryDataModel.h"
#include "RandomObjectFactoryDataModel.h"
#include "VoxelFactoryDataModel.h"

#include "LinearFunctionExpression.h"
#include "LinearCombinationExpression.h"
#include "MultiplicationExpression.h"
#include "CosExpression.h"

#include<iostream>

using namespace Math;

namespace DataModel
{
	DependenceTreeDataModel::DependenceTreeDataModel()
	{
		_factoriesDataModelMap = map<string, LevelFactoryDataModel*>();
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("SimpleObjectFactory", new SimpleObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("ComplexObjectFactory", new ComplexObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("TransformationFactory", new TransformationFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("RandomObjectFactory", new RandomObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("VoxelFactory", new VoxelFactoryDataModel));
	}


	DependenceTreeDataModel::~DependenceTreeDataModel()
	{
	}

	LevelFactory * DependenceTreeDataModel::Read(string filePath)
	{
		// A map of the read expressions, with their name as the key.
		map<string, FloatExpression*>* floatExpressions = new map<string, FloatExpression*>();

		// Test expressions, TO BE REMOVED.
		LinearFunctionExpression* xExpression = new LinearFunctionExpression(Vector3(0.1f, 0.05f, 0));
		LinearFunctionExpression* yExpression = new LinearFunctionExpression(Vector3(0.0f, 1, 0.4f));
		CosExpression* cosExpression = new CosExpression(xExpression);
		LinearCombinationExpression* combinationExpression = new LinearCombinationExpression(yExpression, cosExpression, -1, 10);

		// Adding the test expressions.
		floatExpressions->insert(std::pair<string, FloatExpression*>("combinationExpression", combinationExpression));
		floatExpressions->insert(std::pair<string, FloatExpression*>("xExpression", xExpression));
		floatExpressions->insert(std::pair<string, FloatExpression*>("yExpression", yExpression));
		floatExpressions->insert(std::pair<string, FloatExpression*>("cosExpression", cosExpression));

		// TODO: Read the float expressions from the file specified by filePath.

		// Add the read float epxressions to the static field that all factory data model can access.
		for each (std::pair<string, LevelFactoryDataModel*> couple in _factoriesDataModelMap)
		{
			couple.second->AddFloatExpression(floatExpressions);
		}

		//LevelFactoryDataModel::AddFloatExpression(floatExpressions);

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