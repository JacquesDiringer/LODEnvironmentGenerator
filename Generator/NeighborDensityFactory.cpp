#include "stdafx.h"
#include "NeighborDensityFactory.h"
#include "Item.h"
#include "TransformationFactory.h"
#include "Matrix4.h"

#include <unordered_map>
using std::unordered_map;

namespace Generator
{
	NeighborDensityFactory::NeighborDensityFactory()
	{
	}

	NeighborDensityFactory::NeighborDensityFactory(Math::Vector3 voxelSize, Math::FloatExpression* densityExpression, float minimalDensity = 0.5f)
		: _voxelSize(voxelSize), _densityExpression(densityExpression), _minimalDensity(minimalDensity)
	{
		if (voxelSize.X() == 0 || voxelSize.Y() == 0 || voxelSize.Z() == 0)
		{
			throw new std::invalid_argument("None of the dimensions of the voxel size can be 0");
		}

		_rules = vector<Rule*>();
		_defaultFactory = nullptr;
	}


	NeighborDensityFactory::~NeighborDensityFactory()
	{
	}

	void NeighborDensityFactory::GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		ComputeVoxel(parent, childrenNumber, futureTransformation, worldMatrix, itemVector);
	}

	void NeighborDensityFactory::AddRule(vector<bool>conditions, LevelFactory * factory)
	{
		if (conditions.size() != 8)
		{
			throw new std::invalid_argument("This function is made to accept a vector of 8 conditions only.");
		}

		// New 8 values system
		// One value for each vertex of the cube that contains the current "voxel".
		Math::Vector3 fetchCoordinates[8] =
		{
			Math::Vector3(-0.5f, -0.5f, -0.5f),
			Math::Vector3(-0.5f, 0.5f, -0.5f),
			Math::Vector3(0.5f, -0.5f, -0.5f),
			Math::Vector3(0.5f, 0.5f, -0.5f),

			Math::Vector3(-0.5f, -0.5f, 0.5f),
			Math::Vector3(-0.5f, 0.5f, 0.5f),
			Math::Vector3(0.5f, -0.5f, 0.5f),
			Math::Vector3(0.5f, 0.5f, 0.5f),
		};

		// Declare the new rule.
		Rule* newRule = new Rule(factory);
		
		// Then fill it.
		int fetchIndex = 0;
		for each (bool condition in conditions)
		{
			newRule->AddCondition(fetchCoordinates[fetchIndex], condition);
			++fetchIndex;
		}

		AddRule(newRule);
	}

	void NeighborDensityFactory::AddRule(Rule * newRule)
	{
		for each (Rule* rule in _rules)
		{
			if (newRule == rule)
			{
				throw new std::invalid_argument("A rule with the same conditions has already been added.");
			}
		}

		_rules.push_back(ComputeQuarterRotatedRue(newRule, 0));
		_rules.push_back(ComputeQuarterRotatedRue(newRule, 1));
		_rules.push_back(ComputeQuarterRotatedRue(newRule, 2));
		_rules.push_back(ComputeQuarterRotatedRue(newRule, 3));
	}

	void NeighborDensityFactory::ComputeVoxel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		// This is meant for optimization purposes, don't fetch twice at the same coordinates.
		unordered_map<Math::Vector3, bool> fetchedValuesWorldCoordinates;
		
		// Fetch the density values at the right coordinates in the world.
		for each(Rule* currentRule in _rules)
		{
			// Stays true if every condition reveals true.
			bool ruleValidated = true;

			// This for should be exited when ruleValidated becomes false.
			// Otherwise, continue until there are no more rules to check.
			vector<Condition*> conditions = currentRule->GetConditions();
			for(int i = 0; i < conditions.size() && ruleValidated; ++i)
			{
				Condition* currentCondition = conditions[i];

				Math::Vector3 localDomainFetchCoordinates = currentCondition->LocalFetchCoordinates;

				// Then transform to world coordinates by multiplying by the world mattrix of the father.
				//Math::Vector3 worldFetchCoordinates = Math::Matrix4::Multiply(worldMatrix, localDomainFetchCoordinates);
				Math::Vector3 worldFetchCoordinates = Math::Matrix4::Multiply(worldMatrix, localDomainFetchCoordinates);

				bool fetchResult;

				// If these coordinates have already been fetched, retrieve the resulting value from the map.
				unordered_map<Math::Vector3, bool>::iterator worldCoordinatesFetchIterator = fetchedValuesWorldCoordinates.find(worldFetchCoordinates);
				if (worldCoordinatesFetchIterator != fetchedValuesWorldCoordinates.end())
				{
					fetchResult = (*worldCoordinatesFetchIterator).second;
				}
				else
				{
					// Actually performing the fetch thanks to the density function and comparing the value to the minimal density required.
					fetchResult = DensityFunction(worldFetchCoordinates) > _minimalDensity;

					// Store the value in a map for optimization purposes. Don't fetch twice at the same world coordinates.
					fetchedValuesWorldCoordinates.insert(std::pair<Math::Vector3, bool>(worldFetchCoordinates, fetchResult));
				}

				// Invalidate the rule if one of the conditions is false.
				ruleValidated &= fetchResult == currentCondition->ExpectedValue;
			}

			if (ruleValidated)
			{
				// If the fetched values correspond to a rule, retrieve the associated level factory.
				LevelFactory* associatedFactory = currentRule->GetFactory();

				// Then instanciate new items with this factory.
				if (associatedFactory != nullptr)
				{
					int previousSize = itemVector->size();
					
					associatedFactory->GenerateLevel(parent, childrenNumber, futureTransformation, worldMatrix, itemVector);
				}

				return;
			}
		}

		// If no rule has been validated, check if the a default factory has been set.
		if (_defaultFactory != nullptr)
		{
			// If there is a default factory, return the factory's items.
			_defaultFactory->GenerateLevel(parent, childrenNumber, futureTransformation, worldMatrix, itemVector);
		}
	}

	float NeighborDensityFactory::DensityFunction(const Math::Vector3 fetchCoordinates)
	{
		return _densityExpression->Evaluate(fetchCoordinates);
	}

	Rule * NeighborDensityFactory::ComputeQuarterRotatedRue(Rule * originalRule, int rotationCount)
	{
		// Create a transformation factory on top of the original rule factory (extraLayerFactory), to add the rotation.
		// If the sub factory is NULL however, there is no need to put a rotation factory on top of it
		LevelFactory* originalSubFactory = originalRule->GetFactory();
		LevelFactory* extraLayerFactory;
		if (originalSubFactory != nullptr)
		{
			extraLayerFactory = new TransformationFactory(originalSubFactory, Math::Matrix4::CreateRotationY(90.0f * (float)rotationCount));
		}
		else
		{
			extraLayerFactory = nullptr;
		}

		Rule* result = new Rule(extraLayerFactory);


		// Copy the original conditions but only after rotating the local fecth coordinates.
		for each (Condition* currentOriginalCondition in originalRule->GetConditions())
		{
			// Transform the block local coordinates to coordinates in the domain, thus scaling to the voxel size it and then adding the block's local coordinates inside the domain.
			Math::Vector3 voxelUnrotatedCoords = currentOriginalCondition->LocalFetchCoordinates * _voxelSize;
			Math::Vector3 localDomainFetchCoordinates = Math::Vector3();
			switch (rotationCount)
			{
			case 0:
				localDomainFetchCoordinates = voxelUnrotatedCoords;
				break;
			case 1:
				localDomainFetchCoordinates.X(voxelUnrotatedCoords.Z());
				localDomainFetchCoordinates.Y(voxelUnrotatedCoords.Y());
				localDomainFetchCoordinates.Z(-voxelUnrotatedCoords.X());
				break;
			case 2:
				localDomainFetchCoordinates.X(-voxelUnrotatedCoords.X());
				localDomainFetchCoordinates.Y(voxelUnrotatedCoords.Y());
				localDomainFetchCoordinates.Z(-voxelUnrotatedCoords.Z());
				break;
			case 3:
				localDomainFetchCoordinates.X(-voxelUnrotatedCoords.Z());
				localDomainFetchCoordinates.Y(voxelUnrotatedCoords.Y());
				localDomainFetchCoordinates.Z(voxelUnrotatedCoords.X());
			default:
				break;
			}

			result->AddCondition(localDomainFetchCoordinates, currentOriginalCondition->ExpectedValue);
		}

		return result;
	}

	Rule::Rule()
	{
	}

	Rule::Rule(LevelFactory * factory)
		: _factory(factory)
	{
		_conditionsList = vector<Condition*>();
	}

	Rule::~Rule()
	{
	}

	void Rule::AddCondition(Math::Vector3 fetchCoordinates, bool expectedValue)
	{
		Condition* newCondition = new Condition();
		newCondition->LocalFetchCoordinates = fetchCoordinates;
		newCondition->ExpectedValue = expectedValue;

		_conditionsList.push_back(newCondition);
	}

	bool Rule::operator==(const Rule & other)
	{
		vector<Condition*> othersConditions = other.GetConditions();

		if (_conditionsList.size() != othersConditions.size())
		{
			return false;
		}

		for each (Condition* condition in _conditionsList)
		{
			bool matchingOtherCondition = false;

			for each (Condition* otherCondition in othersConditions)
			{
				if (condition->LocalFetchCoordinates == otherCondition->LocalFetchCoordinates
					&& condition->ExpectedValue == condition->ExpectedValue)
				{
					matchingOtherCondition == true;
				}
			}

			if (!matchingOtherCondition)
			{
				return false;
			}
		}

		return true;
	}
}