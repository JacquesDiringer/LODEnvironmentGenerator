#include "stdafx.h"
#include "TransformationFactory.h"
#include "Item.h"


namespace Generator
{
	TransformationFactory::TransformationFactory()
	{
	}

	TransformationFactory::TransformationFactory(LevelFactory* factory, Math::Matrix4 transformation)
		: _factory(factory), _transformation(transformation)
	{
		// Void
	}


	TransformationFactory::~TransformationFactory()
	{
	}

	void TransformationFactory::GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		Math::Matrix4 newTransformation = Math::Matrix4::Multiply(futureTransformation, _transformation);
		Math::Matrix4 newWorldMatrix = Math::Matrix4::Multiply(worldMatrix, _transformation);

		return _factory->GenerateLevel(parent, childrenNumber, newTransformation, newWorldMatrix, itemVector);
	}

}