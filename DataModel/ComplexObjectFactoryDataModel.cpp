#include "stdafx.h"
#include "ComplexObjectFactoryDataModel.h"
#include "ComplexObjectFactory.h"

using std::getline;
using Generator::ComplexObjectFactory;

namespace DataModel
{
	ComplexObjectFactoryDataModel::ComplexObjectFactoryDataModel()
	{
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
			// Then look if this factory has been previously loaded.
			map<string, LevelFactory*>::iterator levelFactoryIt = previousFactories->find(currentLine);
			if (levelFactoryIt == previousFactories->end())
			{
				throw new std::invalid_argument("Children factory not previously read.");
			}

			// Add the found factory as a composer of the currently constructing factory.
			result->AddComposerFactory((*levelFactoryIt).second);

			// Read the newt line.
			getline(*stream, currentLine);
		}

		_factory = result;
		return result;
	}
	void ComplexObjectFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
	}
}
