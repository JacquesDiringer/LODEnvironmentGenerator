#include "stdafx.h"
#include "DependenceTreeDataModel.h"

#include "SimpleObjectFactoryDataModel.h"
#include "ComplexObjectFactoryDataModel.h"
#include "TransformationFactoryDataModel.h"
#include "RandomObjectFactoryDataModel.h"
#include "NeighborDensityFactoryDataModel.h"
#include "ArrayFactoryDataModel.h"

#include "LinearFunctionDataModel.h"
#include "LinearCombinationDataModel.h"
#include "MultiplicationDataModel.h"
#include "CosDataModel.h"
#include "AABDataModel.h"
#include "BooleanOperatorDataModel.h"

#include <iostream>
#include <filesystem>

using namespace Math;


namespace DataModel
{
	DependenceTreeDataModel::DependenceTreeDataModel()
	{
		_factoriesDataModelMap = unordered_map<string, LevelFactoryDataModel*>();
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("SimpleObjectFactory", new SimpleObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("ComplexObjectFactory", new ComplexObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("TransformationFactory", new TransformationFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("RandomObjectFactory", new RandomObjectFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("NeighborDensityFactory", new NeighborDensityFactoryDataModel));
		_factoriesDataModelMap.insert(std::pair<string, LevelFactoryDataModel*>("ArrayFactory", new ArrayFactoryDataModel));

		_floatExpressionsDataModelMap = unordered_map<string, FloatExpressionDataModel*>();
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("LinearFunctionExpression", new LinearFunctionDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("LinearCombinationExpression", new LinearCombinationDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("MultiplicationExpression", new MultiplicationDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("CosExpression", new CosDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("AABExpression", new AABDataModel()));
		_floatExpressionsDataModelMap.insert(std::pair<string, FloatExpressionDataModel*>("BooleanOperatorExpression", new BooleanOperatorDataModel()));

		//_visitedFiles = unordered_set<string>();
		//_previousFactories = unordered_map<string, LevelFactory*>();
	}


	DependenceTreeDataModel::~DependenceTreeDataModel()
	{
	}

	LevelFactory* DependenceTreeDataModel::Read(string filePath)
	{
		unordered_set<string> visitedFiles = unordered_set<string>();
		unordered_map<string, LevelFactory*> previousFactories = unordered_map<string, LevelFactory*>();

		// A map of the read expressions, with their name as the key.
		unordered_map<string, FloatExpression*>* floatExpressions = new unordered_map<string, FloatExpression*>();

		return ReadFile(filePath, visitedFiles, previousFactories, floatExpressions);
	}

	LevelFactory * DependenceTreeDataModel::ReadFile(string filePath, unordered_set<string>& visitedFiles, unordered_map<string, LevelFactory*>& previousFactories, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		// Last factory that has been read, it will be returned to define the root factory.
		LevelFactory* lastFactory = nullptr;

		// Open an input stream to the designated file path.
		ifstream inputStream(filePath, ifstream::in);

		// If the input stream has correctly been opened.
		if (inputStream)
		{
			// Stream reading content.
			string currentLine;
			int previousLineNumber = 0;

			// Read the included files first.
			// Read until we encounter a FloatExpression or Factory declaration.
			while (std::getline(inputStream, currentLine))
			{
				// Ignore empty lines and comments.
				if (currentLine.length() > 0 && currentLine.find("//") == string::npos)
				{
					// If the current line is an include, read the included file recursively first.
					if (currentLine.find("#include") != string::npos)
					{
						char path[400];
						// Parse the line according to the following format : #include "myPath"
						//sscanf(currentLine.c_str(), "#include \"%[^\"]%s", path);
						// Parse the line according to the following format : #include myPath
						sscanf(currentLine.c_str(), "#include %s", path);

						string strPath = string(path);

						// If the file have not already been read, read it.
						if (visitedFiles.find(strPath) == visitedFiles.end())
						{
							ReadFile(strPath, visitedFiles, previousFactories, previousExpressions);
						}
					}
					// If this is a FloatExpression declaration
					else if (_floatExpressionsDataModelMap.find(currentLine) != _floatExpressionsDataModelMap.end())
					{
						inputStream.seekg(previousLineNumber);
						// Then read the float expression.
						ReadFloatExpression(inputStream, previousExpressions);
					}
					// If this is a Factory declaration.
					else if (_factoriesDataModelMap.find(currentLine) != _factoriesDataModelMap.end())
					{
						inputStream.seekg(previousLineNumber);
						// Then read the factory.
						lastFactory = ReadFactories(inputStream, visitedFiles, previousFactories);
					}
				}

				previousLineNumber = inputStream.tellg();
			}
		}
		else
		{
			throw new std::invalid_argument("File not found.");
		}

		// Mark this file as read.
		visitedFiles.insert(filePath);

		// Return the last factory read, it will become the root factory.
		return lastFactory;
	}

	void DependenceTreeDataModel::ReadFloatExpression(std::ifstream &inputStream, unordered_map<string, FloatExpression*>* previousExpressions)
	{
		// Stream reading content.
		string currentLine;
		std::getline(inputStream, currentLine);

		// TODO: Read the float expressions from the file specified by filePath.
		// Ignore empty lines and comments.
		if (currentLine.length() > 0 && currentLine.find("//") == string::npos)
		{
			unordered_map<string, FloatExpressionDataModel*>::iterator expressionIt = _floatExpressionsDataModelMap.find(currentLine);
			if (expressionIt == _floatExpressionsDataModelMap.end())
			{
				throw new std::invalid_argument("There is no data model able to read that kind of expression.");
			}

			// Retrieve the expression data model.
			FloatExpressionDataModel* expressionReader = (*expressionIt).second;
			// Do the reading. This function will also fill floatExpressions.
			FloatExpression* readExpression = expressionReader->Read(&inputStream, previousExpressions);
		}

		// Add the read float epxressions to the static field that all factory data model can access.
		for each (std::pair<string, LevelFactoryDataModel*> couple in _factoriesDataModelMap)
		{
			couple.second->AddFloatExpression(previousExpressions);
		}
	}

	LevelFactory* DependenceTreeDataModel::ReadFactories(std::ifstream &inputStream, unordered_set<string>& visitedFiles, unordered_map<string, LevelFactory*>& previousFactories)
	{
		// Last factory to be read has to be returned.
		LevelFactory* lastFactory = nullptr;

		// Stream reading content.
		string currentLine;
		std::getline(inputStream, currentLine);

		// Get lines until the end of the file.
		// Lines can be empty between factories for easier human reading purposes.
		if (currentLine.length() > 0 && currentLine.find("//") == string::npos)
		{
			// Search for the right data model to read the factory.
			unordered_map<string, LevelFactoryDataModel*>::iterator factoryReaderIt = _factoriesDataModelMap.find(currentLine);
			if (factoryReaderIt == _factoriesDataModelMap.end())
			{
				throw new std::invalid_argument("There is no data model able to read that kind of factory.");
			}

			// Retrieve the factory data model.
			LevelFactoryDataModel* factoryReader = (*factoryReaderIt).second;
			// Do the reading. This function will also fill _previousFactories.
			lastFactory = factoryReader->Read(&inputStream, &previousFactories);
		}

		return lastFactory;
	}

}