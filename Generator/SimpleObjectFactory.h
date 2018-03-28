#pragma once
#include "LevelFactory.h"
#include "Item.h"
#include "SimpleObjectDisplayable.h"

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
		SimpleObjectFactory(const string& modelName, const string& textureName, float expansionDistance, LevelFactory* subLevelFactory);
		~SimpleObjectFactory();

		// Generates children for the parent
		virtual void GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector);

	private:
		SimpleObjectDisplayable * _modelSimpleDisplayable;
		float _expansionDistance;
		LevelFactory* _subLevelFactory;
	};


}