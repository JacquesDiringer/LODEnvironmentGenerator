#include "stdafx.h"
#include "SimpleObjectFactoryDataModel.h"

#include "SimpleObjectFactory.h"
#include "UtilityReaderWriter.h"

using std::getline;
using Generator::SimpleObjectFactory;

namespace DataModel
{
	SimpleObjectFactoryDataModel::SimpleObjectFactoryDataModel()
	{
		_floatExpressions = new unordered_map<string, FloatExpression*>();
	}

	SimpleObjectFactoryDataModel::~SimpleObjectFactoryDataModel()
	{
	}

	LevelFactory * SimpleObjectFactoryDataModel::InternalRead(ifstream* stream, unordered_map<string, LevelFactory*>* previousFactories)
	{
		string currentLine;

		// Variables necessary for currently read factory initilization.
		string modelName;
		string textureName;
		float expansionDistance;

		// Boolean for the visibility planes "and condition".
		bool andCondition;
		// Vector registering the conditional parametric planes.
		vector<Math::ParametricPlane*> planeVector = vector<Math::ParametricPlane*>();

		// String containing the expansionDistance.
		string expansionDistanceString;
		// Name of the subLevelFactory to be read in the file.
		string subLevelFactoryName;

		// Get the model name line.
		getline(*stream, modelName);

		// Get the texture name line.
		getline(*stream, textureName);

		// Get the float distance of expansion of the factory.
		expansionDistance = UtilityReaderWriter::ReadFloat(stream);

		// Get the visibility planes.
		getline(*stream, currentLine);

		if (currentLine == "Begin Visibility Planes")
		{
			//getline(*stream, currentLine);
			// Get the "and condition".
			andCondition = UtilityReaderWriter::ReadBool(stream);

			getline(*stream, currentLine); // This line will get "New Plane".

			while (currentLine != "End Visibility Planes")
			{
				Math::Vector3 planeNormal = UtilityReaderWriter::ReadVector3(stream);
				float wComponent = UtilityReaderWriter::ReadFloat(stream);
				planeVector.push_back(new Math::ParametricPlane(planeNormal, wComponent));

				getline(*stream, currentLine);
			}

			// Get the string name of the sublevel factory.
			getline(*stream, subLevelFactoryName);
		}
		else
		{
			// Get the string name of the sublevel factory.
			subLevelFactoryName = currentLine;
		}

		// Get the sublevel factory according to its name, if it exist.
		LevelFactory* subLevelFactory = GetFactoryByName(subLevelFactoryName, previousFactories);

		// Return the factory to be stored in the map.
		return new SimpleObjectFactory(modelName, textureName, expansionDistance, planeVector, false, subLevelFactory);
	} 

	void SimpleObjectFactoryDataModel::InternalWrite(ofstream* stream, LevelFactory* factoryToWrite)
	{
		throw std::exception("Not implemented");
	}
}