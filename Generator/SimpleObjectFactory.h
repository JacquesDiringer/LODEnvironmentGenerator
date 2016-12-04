#pragma once
#include "LevelFactory.h"
#include "Item.h"

#include <string>

using std::string;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API SimpleObjectFactory :
		public LevelFactory
	{
	public:
		SimpleObjectFactory();
		SimpleObjectFactory(string modelName, string textureName, float expansionDistance, LevelFactory* subLevelFactory);
		~SimpleObjectFactory();

		// Generates children for the parent
		virtual list<Item*> GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation);

	private:
		string _modelName;
		string _textureName;
		float _expansionDistance;
		LevelFactory* _subLevelFactory;
	};


}