#pragma once

#include "Matrix4.h"

#include <list>

using Math::Matrix4;

using std::list;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class Item;

	class GENERATOR_API LevelFactory
	{
	public:
		LevelFactory();
		~LevelFactory();

		// Generates children for the parent
		virtual list<Item*> GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation) = 0;
	};
}