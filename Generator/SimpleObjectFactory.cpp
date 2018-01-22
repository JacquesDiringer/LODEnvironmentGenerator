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

	void SimpleObjectFactory::GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Matrix4& futureTransformation, const Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		shared_ptr<SimpleObjectDisplayable> displayable = make_shared<SimpleObjectDisplayable>(_modelName, _textureName);

		shared_ptr<Item> simpleObject = std::make_shared<Item>(futureTransformation, parent, _expansionDistance, displayable, _subLevelFactory);

		itemVector->push_back(simpleObject);
	}

}