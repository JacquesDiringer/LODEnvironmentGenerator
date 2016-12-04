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

	list<Item*> TransformationFactory::GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation)
	{
		Matrix4* newTransformation = &Matrix4::Multiply(*futureTransformation, _transformation);

		return _factory->GenerateLevel(parent, childrenNumber, newTransformation);
	}

}