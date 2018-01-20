#include "stdafx.h"
#include "TransformationFactory.h"
#include "Item.h"


namespace Generator
{
	TransformationFactory::TransformationFactory()
	{
	}

	TransformationFactory::TransformationFactory(LevelFactory* factory, Matrix4 transformation)
		: _factory(factory), _transformation(transformation)
	{
		// Void
	}


	TransformationFactory::~TransformationFactory()
	{
	}

	void TransformationFactory::GenerateLevel(weak_ptr<Item> parent, int childrenNumber, const Matrix4& futureTransformation, const Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		Matrix4 newTransformation = Matrix4::Multiply(futureTransformation, _transformation);
		Matrix4 newWorldMatrix = Matrix4::Multiply(worldMatrix, _transformation);

		return _factory->GenerateLevel(parent, childrenNumber, newTransformation, newWorldMatrix, itemVector);
	}

}