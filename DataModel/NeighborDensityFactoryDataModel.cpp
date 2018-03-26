#include "stdafx.h"
#include "NeighborDensityFactoryDataModel.h"

#include <vector>

#include "UtilityReaderWriter.h"

using Generator::Rule;
using std::vector;

namespace DataModel
{
	NeighborDensityFactoryDataModel::NeighborDensityFactoryDataModel()
	{
	}

	NeighborDensityFactoryDataModel::~NeighborDensityFactoryDataModel()
	{
	}

	LevelFactory * NeighborDensityFactoryDataModel::InternalRead(ifstream * stream, unordered_map<string, LevelFactory*>* previousFactories)
	{
		string currentLine;
		
		// Read the voxel size.
		Math::Vector3 voxelSize = UtilityReaderWriter::ReadVector3(stream);

		// Read the density expression name.
		getline(*stream, currentLine);

		// Then look if this factory has been previously loaded.
		unordered_map<string, FloatExpression*>::iterator expressionIt = _floatExpressions->find(currentLine);
		if (expressionIt == _floatExpressions->end())
		{
			throw new std::invalid_argument("No FloatExpression with this name has been loaded.");
		}

		// Register the found expression for factory construction.
		FloatExpression* expression = (*expressionIt).second;

		// Read the minimal density float.
		float minimalDensity = UtilityReaderWriter::ReadFloat(stream);

		// Initialize the factory with the read parameters.
		NeighborDensityFactory* result = new NeighborDensityFactory(voxelSize, expression, minimalDensity);

		// Then read the rules to be added to the factory.

		// Read the eventual default block rule.
		// If there is no default block, this line should state the rules adding phase beginning. 
		getline(*stream, currentLine);
		if (currentLine == "Default")
		{
			// Reads the name of the factory.
			getline(*stream, currentLine);
			// Get the corresponding factory.
			LevelFactory* defaultFactory = GetFactoryByName(currentLine, previousFactories);

			// Set the default block in the result factory.
			result->SetDefaultFactory(defaultFactory);

			// Go to the next line, which should state the rules adding phase beginning.
			getline(*stream, currentLine);
		}

		if (currentLine != "Begin AddRules")
		{
			throw new std::invalid_argument("Wrong format.");
		}

		// Get the first rule's type.
		getline(*stream, currentLine);
		while (currentLine != "End AddRules")
		{
			if (currentLine == "8FetchRule")
			{
				NeighborDensityFactoryDataModel::Read8FetchRule(stream, previousFactories, result);
			}
			else if (currentLine == "CustomRule")
			{
				NeighborDensityFactoryDataModel::ReadCustomRule(stream, previousFactories, result);
			}
			else
			{
				throw new std::invalid_argument("Keyword no corresponding to a type of Rule.");
			}
			// Read the newt line. Either a rule factory name or an end marker.
			getline(*stream, currentLine);
		}

		return result;
	}

	void NeighborDensityFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
		throw std::exception("Not implemented");
	}

	void NeighborDensityFactoryDataModel::Read8FetchRule(ifstream * stream, unordered_map<string, LevelFactory*>* previousFactories, NeighborDensityFactory* factory)
	{
		string currentLine;
		// Get the rule factory name.
		getline(*stream, currentLine);
		// Get the corresponding factory.
		LevelFactory* ruleFactory = GetFactoryByName(currentLine, previousFactories);

		if (ruleFactory == NULL)
		{
			//throw new std::invalid_argument("Cannot have a null factory as a rule.");
		}

		// Read the 8 conditions and store them into a list.
		vector<bool> conditions = vector<bool>();
		for (int i = 0; i < 8; i++)
		{
			getline(*stream, currentLine);
			conditions.push_back((bool)std::stoi(currentLine));
		}

		factory->AddRule(conditions, ruleFactory);
	}

	void NeighborDensityFactoryDataModel::ReadCustomRule(ifstream * stream, unordered_map<string, LevelFactory*>* previousFactories, NeighborDensityFactory* factory)
	{
		string currentLine;
		// Get the rule factory name.
		getline(*stream, currentLine);
		// Get the corresponding factory.
		LevelFactory* ruleFactory = GetFactoryByName(currentLine, previousFactories);

		if (ruleFactory == NULL)
		{
			//throw new std::invalid_argument("Cannot have a null factory as a rule.");
		}

		// Rule to be added.
		Rule* newRule = new Rule(ruleFactory);

		getline(*stream, currentLine);

		// Fill the conditions of the Rule. Until the "End of Rule" marker is met.
		while (currentLine != "End AddConditions")
		{
			Math::Vector3 fetchCoordinates = UtilityReaderWriter::ReadVector3(stream);
			bool expectedValue = UtilityReaderWriter::ReadBool(stream);

			// Add the new condition to the Rule.
			newRule->AddCondition(fetchCoordinates, expectedValue);

			getline(*stream, currentLine);
		}

		factory->AddRule(newRule);
	}
}