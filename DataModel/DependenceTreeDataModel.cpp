#include "stdafx.h"
#include "DependenceTreeDataModel.h"

#include "SimpleObjectFactoryDataModel.h"
#include "ComplexObjectFactoryDataModel.h"
#include "TransformationFactoryDataModel.h"
#include "RandomObjectFactoryDataModel.h"
#include "VoxelFactoryDataModel.h"

#include "LinearFunctionDataModel.h"
#include "LinearCombinationDataModel.h"
#include "MultiplicationDataModel.h"
#include "CosDataModel.h"

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

		_floatExpressionsDataModelMap = map<string, FloatExpressionDataModel*>();
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("LinearFunctionExpression", new LinearFunctionDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("LinearCombinationExpression", new LinearCombinationDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("MultiplicationExpression", new MultiplicationDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("CosExpression", new CosDataModel()));
	}


	DependenceTreeDataModel::~DependenceTreeDataModel()
	{
	}

	LevelFactory * DependenceTreeDataModel::Read(string filePath)
	{
		// Last factory that has been read, it will be returned to define the root factory.
		LevelFactory* lastFactory;

		// Open an input stream to the designated file path.
		ifstream inputStream(filePath, ifstream::in);

		// If the input stream has correctly been opened.
		if (inputStream)
		{
			// Stream reading content.
			string currentLine;

			//// Float expressions reading section.

			// A map of the read expressions, with their name as the key.
			map<string, FloatExpression*>* floatExpressions = new map<string, FloatExpression*>();

			while (std::getline(inputStream, currentLine) && currentLine != "End of FloatExpression")
			{
				// TODO: Read the float expressions from the file specified by filePath.
				if (currentLine.length() > 0 && currentLine.find("//") == string::npos)
				{
					map<string, FloatExpressionDataModel*>::iterator expressionIt = _floatExpressionsDataModelMap.find(currentLine);
					if (expressionIt == _floatExpressionsDataModelMap.end())
					{
						throw new std::invalid_argument("There is no data model able to read that kind of expression.");
					}

					// Retrieve the expression data model.
					FloatExpressionDataModel* expressionReader = (*expressionIt).second;
					// Do the reading. This function will also fill floatExpressions.
					FloatExpression* readExpression = expressionReader->Read(&inputStream, floatExpressions);
				}
			}

			// Add the read float epxressions to the static field that all factory data model can access.
			for each (std::pair<string, LevelFactoryDataModel*> couple in _factoriesDataModelMap)
			{
				couple.second->AddFloatExpression(floatExpressions);
			}


			//// Factories reading section.

			// A map of the the factories that have already been read, stored by name.
			// This is done for children dependencies purposes.
			map<string, LevelFactory*>* previousFactories = new map<string, LevelFactory*>();

			// Get lines until the end of the file.
			while (std::getline(inputStream, currentLine))
			{
				// Lines can be empty between factories for easier human reading purposes.
				if (currentLine.length() > 0 && currentLine.find("//") == string::npos)
				{
					// Search for the right data model to read the factory.
					map<string, LevelFactoryDataModel*>::iterator factoryReaderIt = _factoriesDataModelMap.find(currentLine);
					if (factoryReaderIt == _factoriesDataModelMap.end())
					{
						throw new std::invalid_argument("There is no data model able to read that kind of factory.");
					}

					// Retrieve the factory data model.
					LevelFactoryDataModel* factoryReader = (*factoryReaderIt).second;
					// Do the reading. This function will also fill previousFactories.
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