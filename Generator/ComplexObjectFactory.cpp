#include "stdafx.h"
#include "ComplexObjectFactory.h"


namespace Generator
{
	ComplexObjectFactory::ComplexObjectFactory()
	{
		_itemOccurrences = vector<LevelFactory*>();
	}


	ComplexObjectFactory::~ComplexObjectFactory()
	{
	}

	void ComplexObjectFactory::AddComposerFactory(LevelFactory* composerFactory)
	{
		_itemOccurrences.push_back(composerFactory);
	}

	vector<Item*> ComplexObjectFactory::GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix)
	{
		vector<Item*> result = vector<Item*>();

		int currentFactoryId = 0;
		for each (LevelFactory* currentFactory in _itemOccurrences)
		{
			++currentFactoryId;

			vector<Item*> generatedItems = currentFactory->GenerateLevel(parent, childrenNumber * currentFactoryId, futureTransformation, worldMatrix);

			int idCounter = 0;
			for each (Item* currentItem in generatedItems)
			{
				Vector3 position = currentItem->GetWorldMatrix().Position();
				// TODO: This is probably what leads to random objects that are not distributed randomly but more like following a diagonal.
				currentItem->SetId(idCounter + position.X() + position.Y() + position.Z());
				result.push_back(currentItem);

				++idCounter;
			}
		}

		return result;
	}
}