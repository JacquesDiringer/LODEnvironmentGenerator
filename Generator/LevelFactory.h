#pragma once

#include <list>

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
		virtual list<Item*> GenerateLevel(Item* parent, int childrenNumber) = 0;
	};


}