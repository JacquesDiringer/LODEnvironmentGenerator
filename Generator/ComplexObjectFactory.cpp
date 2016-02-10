#include "stdafx.h"
#include "ComplexObjectFactory.h"


namespace Generator
{
	ComplexObjectFactory::ComplexObjectFactory()
	{
		_itemOccurrences = list<LevelFactory*>();
	}


	ComplexObjectFactory::~ComplexObjectFactory()
	{
	}

	void ComplexObjectFactory::AddComposerFactory(LevelFactory* composerFactory)
	{
		_itemOccurrences.push_back(composerFactory);
	}

	list<Item*> ComplexObjectFactory::GenerateLevel(Item* parent, int childrenNumber)
	{
		list<Item*> result = list<Item*>();

		int currentFactoryId = 0;
		for each (LevelFactory* currentFactory in _itemOccurrences)
		{
			++currentFactoryId;

			list<Item*> generatedItems = currentFactory->GenerateLevel(parent, childrenNumber * currentFactoryId);

			int idCounter = 0;
			for each (Item* currentItem in generatedItems)
			{
				//currentItem->SetRelativeMatrix(Matrix4::Multiply(currentMatrix, currentItem->GetRelativeMatrix()));
				Vector3 position = currentItem->GetWorldMatrix().Position();
				currentItem->SetId(idCounter + position.X() + position.Y() + position.Z());
				result.push_back(currentItem);

				++idCounter;
			}
		}

		return result;
	}
}