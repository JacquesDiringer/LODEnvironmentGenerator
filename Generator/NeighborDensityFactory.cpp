#include "stdafx.h"
#include "NeighborDensityFactory.h"
#include "Item.h"

namespace Generator
{
	NeighborDensityFactory::NeighborDensityFactory()
	{
	}

	NeighborDensityFactory::NeighborDensityFactory(Vector3 voxelSize, FloatExpression* densityExpression, bool isDomainLimited, float minimalDensity = 0.5f)
		: _voxelSize(voxelSize), _densityExpression(densityExpression), _isDomainLimited(isDomainLimited), _minimalDensity(minimalDensity)
	{
		if (voxelSize.X() == 0 || voxelSize.Y() == 0 || voxelSize.Z() == 0)
		{
			throw new std::invalid_argument("None of the dimensions of the voxel size can be 0");
		}

		_rules = list<Rule*>();
	}


	NeighborDensityFactory::~NeighborDensityFactory()
	{
	}

	list<Item*> NeighborDensityFactory::GenerateLevel(Item * parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix)
	{
		return ComputeVoxel(parent, childrenNumber, futureTransformation, worldMatrix);
	}

	void NeighborDensityFactory::AddRule(list<bool>conditions, LevelFactory * factory)
	{
		if (conditions.size() != 8)
		{
			throw new std::invalid_argument("This function is made to accept a list of 8 conditions only.");
		}

		// New 8 values system
		// One value for each vertex of the cube that contains the current "voxel".
		Vector3 fetchCoordinates[8] =
		{
			Vector3(-0.5f, -0.5f, -0.5f),
			Vector3(-0.5f, 0.5f, -0.5f),
			Vector3(0.5f, -0.5f, -0.5f),
			Vector3(0.5f, 0.5f, -0.5f),

			Vector3(-0.5f, -0.5f, 0.5f),
			Vector3(-0.5f, 0.5f, 0.5f),
			Vector3(0.5f, -0.5f, 0.5f),
			Vector3(0.5f, 0.5f, 0.5f),
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

	list<Item*> NeighborDensityFactory::ComputeVoxel(Item * parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix)
	{
		// This is meant for optimization purposes, don't fetch twice at the same coordinates.
		map<Vector3, bool> fetchedValuesWorldCoordinates;

		list<Item*> newItems = list<Item*>();

		Matrix4 currentRotationMatrix = Matrix4::Identity();
		Matrix4 quarterRotationMatrix = Matrix4::CreateRotationY(90);
		// Calculations have to be done 4 times, rotating the fetching coordinates in the 4 cardinal directions to reduce the combination possibilities.
		// The calculations can stop as spoon as a result is found. We don't want symetric conditions on the Y axis to spawn 4 objects at the same spot.
		for (int rotationCount = 0; rotationCount < 4 && newItems.size() == 0; rotationCount++)
		{
			// Fetch the density values at the right coordinates in the world.
			for each(Rule* currentRule in _rules)
			{
				// Stays true if every condition reveals true.
				bool ruleValidated = true;

				for each(Condition* currentCondition in currentRule->GetConditions())
				{
					// Transform the block local coordinates to coordinates in the domain, thus scaling to the voxel size it and then adding the block's local coordinates inside the domain.
					Vector3 localDomainFetchCoordinates = Matrix4::Multiply(currentRotationMatrix, currentCondition->LocalFetchCoordinates * _voxelSize);
					// Then transforming to world coordinates by multiplying by the world mattrix of the father.
					Vector3 worldFetchCoordinates = Matrix4::Multiply(*worldMatrix, localDomainFetchCoordinates);

					bool fetchResult;

					// If these coordinates have already been fetched, retrieve the resulting value from the map.
					map<Vector3, bool>::iterator worldCoordinatesFetchIterator = fetchedValuesWorldCoordinates.find(worldFetchCoordinates);
					if (worldCoordinatesFetchIterator != fetchedValuesWorldCoordinates.end())
					{
						fetchResult = (*worldCoordinatesFetchIterator).second;
					}
					else
					{
						// Actually performing the fetch thanks to the density function and comparing the value to the minimal density required.
						fetchResult = DensityFunction(worldFetchCoordinates) > _minimalDensity;

						// Store the value in a map for optimization purposes. Don't fetch twice at the same world coordinates.
						fetchedValuesWorldCoordinates.insert(std::pair<Vector3, bool>(worldFetchCoordinates, fetchResult));
					}

					// Invalidate the rule if one of the conditions is false.
					ruleValidated &= fetchResult == currentCondition->ExpectedValue;
				}

				if (ruleValidated)
				{
					// If the fetched values correspond to a rule, retrieve the associated level factory.
					LevelFactory* associatedFactory = currentRule->GetFactory();

					// Then instanciate new items with this factory.
					list<Item*> generatedItems = associatedFactory->GenerateLevel(parent, childrenNumber, futureTransformation, worldMatrix);

					int idCounter = 0;
					for each (Item* currentItem in generatedItems)
					{
						// Correct the rotation of the items.
						currentItem->SetRelativeMatrix(currentItem->GetRelativeMatrix() * currentRotationMatrix);
						Vector3 position = currentItem->GetWorldMatrix().Position();
						// Give them a better ID.
						currentItem->SetId(idCounter + position.X() + position.Y() + position.Z());
						++idCounter;
					}

					return generatedItems;
				}
			}

			currentRotationMatrix = quarterRotationMatrix*currentRotationMatrix;
		}

		return newItems;
	}

	float NeighborDensityFactory::DensityFunction(const Vector3 fetchCoordinates)
	{
		return _densityExpression->Evaluate(fetchCoordinates);
	}

	NeighborDensityFactory::Rule::Rule()
	{
	}

	NeighborDensityFactory::Rule::Rule(LevelFactory * factory)
		: _factory(factory)
	{
		_conditionsList = list<Condition*>();
	}

	NeighborDensityFactory::Rule::~Rule()
	{
	}

	void NeighborDensityFactory::Rule::AddCondition(Vector3 fetchCoordinates, bool expectedValue)
	{
		Condition* newCondition = new Condition();
		newCondition->LocalFetchCoordinates = fetchCoordinates;
		newCondition->ExpectedValue = expectedValue;

		_conditionsList.push_back(newCondition);
	}

	bool NeighborDensityFactory::Rule::operator==(const Rule & other)
	{
		list<Condition*> othersConditions = other.GetConditions();

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