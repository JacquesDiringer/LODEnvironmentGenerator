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

		_rules = map<list<bool>, LevelFactory*>();
	}


	NeighborDensityFactory::~NeighborDensityFactory()
	{
	}

	list<Item*> NeighborDensityFactory::GenerateLevel(Item * parent, int childrenNumber, const Matrix4* futureTransformation)
	{
		return ComputeVoxel(parent, childrenNumber, futureTransformation);
	}

	void NeighborDensityFactory::AddRule(bool const conditions[8], LevelFactory * factory)
	{
		list<bool> conditionsList = list<bool>();

		for each (bool currentCondition in conditions)
		{
			conditionsList.push_back(currentCondition);
		}

		AddRule(conditionsList, factory);
	}

	void NeighborDensityFactory::AddRule(list<bool>conditions, LevelFactory * factory)
	{
		for each (std::pair<list<bool>, LevelFactory*> rulePair in _rules)
		{
			if (rulePair.first == conditions)
			{
				throw new std::invalid_argument("A rule with the same conditions has already been added.");
			}
		}

		_rules.insert(std::pair<list<bool>, LevelFactory*>(conditions, factory));
	}

	list<Item*> NeighborDensityFactory::ComputeVoxel(Item * parent, int childrenNumber, const Matrix4* futureTransformation)
	{
		list<Item*> newItems = list<Item*>();

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

		Matrix4 currentRotationMatrix = Matrix4::Identity();
		Matrix4 quarterRotationMatrix = Matrix4::CreateRotationY(90);
		// Calculations have to be done 4 times, rotating the fetching coordinates in the 4 cardinal directions to reduce the combination possibilities.
		// The calculations can stop as spoon as a result is found. We don't want symetric conditions on the Y axis to spawn 4 objects at the same spot.
		for (int rotationCount = 0; rotationCount < 4 && newItems.size() == 0; rotationCount++)
		{
			list<bool>fetchedValues;

			// Fetch the density values at the right coordinates in the world.
			for (int fetchIndex = 0; fetchIndex < 8; fetchIndex++)
			{
				// Transform the block local coordinates to coordinates in the domain, thus scaling to the voxel size it and then adding the block's local coordinates inside the domain.
				Vector3 localDomainFetchCoordinates = Matrix4::Multiply(currentRotationMatrix, fetchCoordinates[fetchIndex] * _voxelSize);
				// Then transforming to world coordinates by multiplying by the world mattrix of the father.
				Vector3 worldFetchCoordinates = Matrix4::Multiply(*futureTransformation, localDomainFetchCoordinates);
				// Actually performing the fetch thanks to the density function and comparing the value to the minimal density required.
				fetchedValues.push_back(DensityFunction(worldFetchCoordinates) > _minimalDensity);
			}

			// Compare the density values to the _rules stored.
			std::map<list<bool>, LevelFactory*>::iterator correspondingPairIterator = _rules.find(fetchedValues);
			if (correspondingPairIterator != _rules.end())
			{
				// If the fetched values correspond to a rule, retrieve the associated level factory.
				LevelFactory* associatedFactory = (*correspondingPairIterator).second;

				// Then instanciate new items with this factory.
				list<Item*> generatedItems = associatedFactory->GenerateLevel(parent, childrenNumber, futureTransformation);

				int idCounter = 0;
				for each (Item* currentItem in generatedItems)
				{
					//currentItem->SetRelativeMatrix(currentRotationMatrix * currentItem->GetRelativeMatrix());
					currentItem->SetRelativeMatrix(currentItem->GetRelativeMatrix() * currentRotationMatrix);
					Vector3 position = currentItem->GetWorldMatrix().Position();
					currentItem->SetId(idCounter + position.X() + position.Y() + position.Z());
					// And put them in the returned list.
					newItems.push_back(currentItem);
					++idCounter;
				}
			}

			currentRotationMatrix = quarterRotationMatrix*currentRotationMatrix;
		}

		return newItems;
	}

	float NeighborDensityFactory::DensityFunction(const Vector3 fetchCoordinates)
	{
		return _densityExpression->Evaluate(fetchCoordinates);
		//return (fetchCoordinates.Y() < 0) && (fetchCoordinates.X() > 10) || (fetchCoordinates.Y() < 0) && (fetchCoordinates.X() < 0) || fetchCoordinates.Z() < 0 ? 1.0f : 0.0f;

		//return (fetchCoordinates.Y() + std::cos(fetchCoordinates.X() / 10.0) * 20.0 < 0) && fetchCoordinates.Z() < 0 ? 1.0f : 0.0f;
		//return fetchCoordinates.Y() + std::cos(fetchCoordinates.X() / 10.0) * 10.0 + std::cos(fetchCoordinates.Z() / 5.0) * 5.0 < 0 ? 1.0f : 0.0f;
	}

}