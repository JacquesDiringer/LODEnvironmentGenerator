#pragma once
#include "LevelFactory.h"
#include "Vector3.h"
#include "ComplexObjectFactory.h"
#include "TransformationFactory.h"

using namespace Math;

using std::list;

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
		ArrayFactory(int xCount, int yCount, int zCount, Vector3 boxSize, LevelFactory* factory);
		~ArrayFactory();

		// Generates children for the parent
		virtual list<Item*> GenerateLevel(Item* parent, int childrenNumber);

	private:
		ComplexObjectFactory _arrayFactory;
	};
}