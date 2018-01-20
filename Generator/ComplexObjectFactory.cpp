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

	void ComplexObjectFactory::GenerateLevel(weak_ptr<Item> parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		int currentFactoryId = 0;
		for each (LevelFactory* currentFactory in _itemOccurrences)
		{
			++currentFactoryId;

			currentFactory->GenerateLevel(parent, currentFactoryId, futureTransformation, worldMatrix, itemVector);
		}
	}
}