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

	vector<Item*> TransformationFactory::GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix)
	{
		Matrix4* newTransformation = &Matrix4::Multiply(*futureTransformation, _transformation);
		Matrix4* newWorldMatrix = &Matrix4::Multiply(*worldMatrix, _transformation);

		return _factory->GenerateLevel(parent, childrenNumber, newTransformation, newWorldMatrix);
	}

}