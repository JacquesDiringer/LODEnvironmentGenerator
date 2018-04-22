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

	void ComplexObjectFactory::GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		int currentFactoryId = 0;
		for each (LevelFactory* currentFactory in _itemOccurrences)
		{
			++currentFactoryId;

			currentFactory->GenerateLevel(parent, currentFactoryId, futureTransformation, worldMatrix, itemVector);
		}
	}
}