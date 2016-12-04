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
		//Matrix4* newTransformation = &Matrix4::Multiply(_transformation, *futureTransformation);
		Matrix4* newTransformation = &Matrix4::Multiply(*futureTransformation, _transformation);

		//list<Item*> result = _factory->GenerateLevel(parent, childrenNumber, newTransformation);

		//// TODO : Check for validity
		//for each (Item* currentItem in result)
		//{
		//	currentItem->SetRelativeMatrix(Matrix4::Multiply(_transformation, currentItem->GetRelativeMatrix()));
		//}

		//return result;

		return _factory->GenerateLevel(parent, childrenNumber, newTransformation);
	}

}