#include "stdafx.h"
#include "ArrayFactory.h"
#include "Matrix4.h"


namespace Generator
{
	ArrayFactory::ArrayFactory()
	{
	}

	ArrayFactory::ArrayFactory(int xCount, int yCount, int zCount, Vector3 boxSize, LevelFactory * factory)
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
					Matrix4 transflationMatrix = Matrix4::CreateTranslation(Vector3(
						(xIter + 0.5f) * boxSize.X(),
						(yIter + 0.5f) * boxSize.Y(),
						(zIter + 0.5f) * boxSize.Z()));

					_arrayFactory.AddComposerFactory(new TransformationFactory(factory, transflationMatrix));
				}
			}
		}
	}

	ArrayFactory::~ArrayFactory()
	{
	}

	list<Item*> ArrayFactory::GenerateLevel(Item * parent, int childrenNumber, const Matrix4* futureTransformation)
	{
		return _arrayFactory.GenerateLevel(parent, childrenNumber, futureTransformation);
	}
}