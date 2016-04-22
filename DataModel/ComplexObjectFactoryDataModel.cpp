#include "stdafx.h"
#include "ComplexObjectFactoryDataModel.h"
#include "ComplexObjectFactory.h"

using std::getline;
using Generator::ComplexObjectFactory;

namespace DataModel
{
	ComplexObjectFactoryDataModel::ComplexObjectFactoryDataModel()
	{
		_floatExpressions = new map<string, FloatExpression*>();
	}

	ComplexObjectFactoryDataModel::~ComplexObjectFactoryDataModel()
	{
	}
	LevelFactory * ComplexObjectFactoryDataModel::InternalRead(ifstream * stream, map<string, LevelFactory*>* previousFactories)
	{
		ComplexObjectFactory* result = new ComplexObjectFactory();

		string currentLine;
		// Get the line that should state the composer adding phase beginning.
		getline(*stream, currentLine);
		if (currentLine != "Begin AddComposerFactory")
		{
			throw new std::invalid_argument("Wrong format.");
		}

		// Get the first composer name.
		getline(*stream, currentLine);
		while (currentLine != "End AddComposerFactory")
		{
			// Get the composer factory according to its name, if it exist.
			LevelFactory* composerFactory = GetFactoryByName(currentLine, previousFactories);

			if (composerFactory != NULL)
			{
				// Add the found factory as a composer of the currently constructing factory.
				result->AddComposerFactory(composerFactory);
			}

			// Read the newt line. Either a new composer factory or an end marker.
			getline(*stream, currentLine);
		}

		_factory = result;
		return result;
	}
	void ComplexObjectFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
		throw std::exception("Not implemented");
	}
}
