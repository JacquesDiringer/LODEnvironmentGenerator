#include "stdafx.h"
#include "SimpleObjectFactory.h"
#include "SimpleObjectDisplayable.h"


namespace Generator
{
	SimpleObjectFactory::SimpleObjectFactory()
	{
	}

	SimpleObjectFactory::SimpleObjectFactory(const string& modelName, const string& textureName, float expansionDistance, const vector<Math::ParametricPlane*>& visibilityPlanes, bool andCondition, LevelFactory* subLevelFactory)
		: _expansionDistance(expansionDistance), _visibilityPlanes(visibilityPlanes), _visibilityPlanesAndCondition(andCondition), _subLevelFactory(subLevelFactory)
	{
		_modelSimpleDisplayable = new SimpleObjectDisplayable(modelName, textureName);
	}


	SimpleObjectFactory::~SimpleObjectFactory()
	{
	}

	void SimpleObjectFactory::GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		shared_ptr<SimpleObjectDisplayable> displayable = make_shared<SimpleObjectDisplayable>(_modelSimpleDisplayable);

		shared_ptr<Item> simpleObject = std::make_shared<Item>(futureTransformation, parent, _expansionDistance, _visibilityPlanes, _visibilityPlanesAndCondition, displayable, _subLevelFactory);

		itemVector->push_back(simpleObject);
	}

}