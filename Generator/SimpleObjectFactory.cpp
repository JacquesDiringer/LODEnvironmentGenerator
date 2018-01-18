#include "stdafx.h"
#include "SimpleObjectFactory.h"
#include "SimpleObjectDisplayable.h"


namespace Generator
{
	SimpleObjectFactory::SimpleObjectFactory()
	{
	}

	SimpleObjectFactory::SimpleObjectFactory(string modelName, string textureName, float expansionDistance, LevelFactory* subLevelFactory)
		: _modelName(modelName), _textureName(textureName), _expansionDistance(expansionDistance), _subLevelFactory(subLevelFactory)
	{
		// Void
	}


	SimpleObjectFactory::~SimpleObjectFactory()
	{
	}

	void SimpleObjectFactory::GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix, vector<Item*>* itemVector)
	{
		SimpleObjectDisplayable* displayable = new SimpleObjectDisplayable(_modelName, _textureName);

		Item* simpleObject = new Item(*futureTransformation, parent, _expansionDistance, displayable, _subLevelFactory);

		itemVector->push_back(simpleObject);
	}

}