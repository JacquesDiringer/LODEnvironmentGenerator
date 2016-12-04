#include "stdafx.h"
#include "VoxelFactoryDataModel.h"

#include "VoxelFactory.h"
#include "FloatExpressionDataModel.h"
#include "UtilityReaderWriter.h"

using Generator::VoxelFactory;
using std::list;

namespace DataModel
{
	VoxelFactoryDataModel::VoxelFactoryDataModel()
	{
	}

	VoxelFactoryDataModel::~VoxelFactoryDataModel()
	{
	}

	LevelFactory * VoxelFactoryDataModel::InternalRead(ifstream * stream, map<string, LevelFactory*>* previousFactories)
	{
		string currentLine;
		
		// Read the voxel size.
		Vector3 voxelSize = FloatExpressionDataModel::ReadVector3(stream);

		// Read the domain size.
		Vector3 domainSize = FloatExpressionDataModel::ReadVector3(stream);

		// Read the density expression name.
		getline(*stream, currentLine);

		// Then look if this factory has been previously loaded.
		map<string, FloatExpression*>::iterator expressionIt = _floatExpressions->find(currentLine);
		if (expressionIt == _floatExpressions->end())
		{
			throw new std::invalid_argument("No FloatExpression with this name has been loaded.");
		}

		// Register the found expression for factory construction.
		FloatExpression* expression = (*expressionIt).second;

		// Read the domainIsLimited boolean.
		getline(*stream, currentLine);
		bool isDomainLimited = std::stoi(currentLine);

		// Read the minimal density float.
		float minimalDensity = UtilityReaderWriter::ReadFloat(stream);

		// Initialize the factory with the read parameters.
		VoxelFactory* result = new VoxelFactory(voxelSize, domainSize, expression, isDomainLimited, minimalDensity);

		// Then read the rules to be added to the factory.

		// Get the line that should state the rules adding phase beginning.
		getline(*stream, currentLine);
		if (currentLine != "Begin AddRules")
		{
			throw new std::invalid_argument("Wrong format.");
		}

		// Get the first rule factory name.
		getline(*stream, currentLine);
		while (currentLine != "End AddRules")
		{
			// Get the corresponding factory.
			LevelFactory* ruleFactory = GetFactoryByName(currentLine, previousFactories);

			if (ruleFactory == NULL)
			{
				throw new std::invalid_argument("Cannot have a null factory as a rule.");
			}

			// Read the 8 conditions and store them into a list.
			list<bool> conditions = list<bool>();
			for (int i = 0; i < 8; i++)
			{
				getline(*stream, currentLine);
				conditions.push_back((bool)std::stoi(currentLine));
			}

			result->AddRule(conditions, ruleFactory);

			// Read the newt line. Either a rule factory name or an end marker.
			getline(*stream, currentLine);
		}

		return result;
	}

	void VoxelFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
		throw std::exception("Not implemented");
	}
}