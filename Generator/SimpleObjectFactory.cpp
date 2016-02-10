#include "stdafx.h"
#include "SimpleObjectFactory.h"
#include "SimpleObjectDisplayable.h"


namespace Generator
{
	SimpleObjectFactory::SimpleObjectFactory()
	{
	}

	SimpleObjectFactory::SimpleObjectFactory(string modeName, string textureName, float expansionDistance, LevelFactory* subLevelFactory)
		: _modelName(modeName), _textureName(textureName), _expansionDistance(expansionDistance), _subLevelFactory(subLevelFactory)
	{
		// Void
	}


	SimpleObjectFactory::~SimpleObjectFactory()
	{
	}

	list<Item*> SimpleObjectFactory::GenerateLevel(Item* parent, int childrenNumber)
	{
		list<Item*> result = list<Item*>();

		SimpleObjectDisplayable* displayable = new SimpleObjectDisplayable(_modelName, _textureName);

		Item* simpleObject = new Item(Matrix4::Identity(), parent, _expansionDistance, displayable, _subLevelFactory);

		result.push_back(simpleObject);

		return result;
	}

}