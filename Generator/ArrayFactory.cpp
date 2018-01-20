#include "stdafx.h"
#include "ArrayFactory.h"
#include "Matrix4.h"


namespace Generator
{
	ArrayFactory::ArrayFactory()
	{
	}

	ArrayFactory::ArrayFactory(int xCount, int yCount, int zCount, Vector3 boxSize, bool centered, LevelFactory * factory)
	{
		// The ArrayFactory is just a ComplexObjectFactory containing TransformationFactories putting the objects in the right spot according to their array index.
		_arrayFactory = ComplexObjectFactory();

		for (int xIter = 0; xIter < xCount; xIter++)
		{
			for (int yIter = 0; yIter < yCount; yIter++)
			{
				for (int zIter = 0; zIter < zCount; zIter++)
				{
					// Translation for the TransformationFactory that will put the child factory at the right spot according to it's array index.
					Matrix4 transformationMatrix;
					if (centered)
					{
						transformationMatrix = Matrix4::CreateTranslation(Vector3(
							boxSize.X() *(-0.5f * (xCount - 1) + xIter),
							boxSize.Y() *(-0.5f * (yCount - 1) + yIter),
							boxSize.Z() *(-0.5f * (zCount - 1) + zIter)));
					}
					else
					{
						transformationMatrix = Matrix4::CreateTranslation(Vector3(
							(xIter + 0.5f) * boxSize.X(),
							(yIter + 0.5f) * boxSize.Y(),
							(zIter + 0.5f) * boxSize.Z()));
					}

					_arrayFactory.AddComposerFactory(new TransformationFactory(factory, transformationMatrix));
				}
			}
		}
	}

	ArrayFactory::~ArrayFactory()
	{
	}

	void ArrayFactory::GenerateLevel(weak_ptr<Item> parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix, vector<shared_ptr<Item>>* itemVector)
	{
		_arrayFactory.GenerateLevel(parent, childrenNumber, futureTransformation, worldMatrix, itemVector);
	}
}