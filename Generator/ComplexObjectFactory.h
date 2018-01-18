#pragma once
#include "LevelFactory.h"
#include "Item.h"
#include "Matrix4.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API ComplexObjectFactory :
		public LevelFactory
	{
	public:
		ComplexObjectFactory();
		~ComplexObjectFactory();

		void AddComposerFactory(LevelFactory* composerFactory);

		// Generates children for the parent
		virtual void GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation, const Matrix4* worldMatrix, vector<Item*>* itemVector);

	private:
		vector<LevelFactory*> _itemOccurrences;
	};
}