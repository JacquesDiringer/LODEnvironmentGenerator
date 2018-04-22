#include "stdafx.h"
#include "NeighborDensityFactory.h"
#include "Item.h"

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

		_rules.push_back(newRule);
	}

	void NeighborDensityFactory::ComputeVoxel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		// This is meant for optimization purposes, don't fetch twice at the same coordinates.
		unordered_map<Math::Vector3, bool> fetchedValuesWorldCoordinates;

		Math::Matrix4 currentRotationMatrix = Math::Matrix4::Identity();
		Math::Matrix4 quarterRotationMatrix = Math::Matrix4::CreateRotationY(90);
		// Calculations have to be done 4 times, rotating the fetching coordinates in the 4 cardinal directions to reduce the combination possibilities.
		// The calculations can stop as spoon as a result is found. We don't want symetric conditions on the Y axis to spawn 4 objects at the same spot.
		for (int rotationCount = 0; rotationCount < 4; ++rotationCount)
		{
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

					// Transform the block local coordinates to coordinates in the domain, thus scaling to the voxel size it and then adding the block's local coordinates inside the domain.
					Math::Vector3 voxelUnrotatedCoords = currentCondition->LocalFetchCoordinates * _voxelSize;
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

					// Then transform to world coordinates by multiplying by the world mattrix of the father.
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
						// TODO: multiply the currentRotationMatrix to worldMatrix and futureTransformation
						associatedFactory->GenerateLevel(parent, childrenNumber, futureTransformation, worldMatrix, itemVector);

						// Compute the number of new elements (that should be at the end of the vector), so that we can adjust their matrices.
						int newElementsCount = itemVector->size() - previousSize;

						for(; newElementsCount > 0; --newElementsCount)
						{
							// Select the last elements that have just been added on the lines "GenerateLevel" above.
							shared_ptr<Item> itemToCorrect = (*itemVector)[itemVector->size() - newElementsCount];

							// Correct the rotation of the item.
							itemToCorrect->SetRelativeMatrix(itemToCorrect->GetRelativeMatrix() * currentRotationMatrix);
						}
					}

					return;
				}
			}

			currentRotationMatrix = quarterRotationMatrix*currentRotationMatrix;
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