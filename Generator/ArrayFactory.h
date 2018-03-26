#pragma once
#include "LevelFactory.h"
#include "Vector3.h"
#include "ComplexObjectFactory.h"
#include "TransformationFactory.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API ArrayFactory :
		public LevelFactory
	{
	public:
		ArrayFactory();
		// Each instance will be considered to be at the center of a box of dimension "boxSize", these boxes will be instanciated side by side.
		ArrayFactory(int xCount, int yCount, int zCount, Math::Vector3 boxSize, bool centered, LevelFactory* factory);
		~ArrayFactory();

		// Generates children for the parent
		virtual void GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector);

	private:
		ComplexObjectFactory _arrayFactory;
	};
}