#include "stdafx.h"
#include "ArrayFactoryDataModel.h"

#include "ArrayFactory.h"
#include "UtilityReaderWriter.h"

using Generator::ArrayFactory;

namespace DataModel
{
	ArrayFactoryDataModel::ArrayFactoryDataModel()
	{
	}


	ArrayFactoryDataModel::~ArrayFactoryDataModel()
	{
	}

	LevelFactory * ArrayFactoryDataModel::InternalRead(ifstream * stream, map<string, LevelFactory*>* previousFactories)
	{
		// Name of the subLevelFactory to be read in the file.
		string subLevelFactoryName;
		// Get the string name of the sublevel factory.
		getline(*stream, subLevelFactoryName);
		// Get the sublevel factory according to its name, if it exist.
		LevelFactory* subLevelFactory = GetFactoryByName(subLevelFactoryName, previousFactories);

		// The sublevel has to exist.
		if (subLevelFactory == NULL)
		{
			throw new std::invalid_argument("A transformation factory should always have a sublevel.");
		}

		// Dimensions of the array, to be read.
		int xCount = UtilityReaderWriter::ReadFloat(stream);
		int	yCount = UtilityReaderWriter::ReadFloat(stream);
		int	zCount = UtilityReaderWriter::ReadFloat(stream);

		float boxFloats[3];

		for (int i = 0; i < 3; ++i)
		{
			boxFloats[i] = UtilityReaderWriter::ReadFloat(stream);
		}

		// Spacing of the elements in the array.
		Vector3 boxSize = Vector3(boxFloats[0],
			boxFloats[1],
			boxFloats[2]);

		return new ArrayFactory(xCount, yCount, zCount, boxSize, subLevelFactory);
	}

	void ArrayFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
	}

}