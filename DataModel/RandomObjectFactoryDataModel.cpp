#include "stdafx.h"
#include "RandomObjectFactoryDataModel.h"

#include "RandomObjectFactory.h"

using Generator::RandomObjectFactory;


namespace DataModel
{
	RandomObjectFactoryDataModel::RandomObjectFactoryDataModel()
	{
		_floatExpressions = new map<string, FloatExpression*>();
	}

	RandomObjectFactoryDataModel::~RandomObjectFactoryDataModel()
	{
	}

	LevelFactory * RandomObjectFactoryDataModel::InternalRead(ifstream * stream, map<string, LevelFactory*>* previousFactories)
	{
		RandomObjectFactory* result = new RandomObjectFactory();

		string currentLine;
		// Get the line that should state the random factory adding phase beginning.
		getline(*stream, currentLine);
		if (currentLine != "Begin AddRandomFactory")
		{
			throw new std::invalid_argument("Wrong format.");
		}

		// Get the first random factory probability.
		getline(*stream, currentLine);
		while (currentLine != "End AddRandomFactory")
		{
			// Convert the read string to a proper probability float.
			float probability = std::stof(currentLine);
		
			// Get the random factory name.
			getline(*stream, currentLine);
			// Get the random factory according to its name, if it exist.
			LevelFactory* composerFactory = GetFactoryByName(currentLine, previousFactories);
			
			// Add the found factory as a random factory of the currently constructing factory.
			result->AddAlternativeFactory(probability, composerFactory);

			// Read the newt line. Either a random factory probability or an end marker.
			getline(*stream, currentLine);
		}

		_factory = result;
		return _factory;
	}

	void RandomObjectFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
	}
}