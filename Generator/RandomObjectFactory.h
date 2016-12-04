#pragma once
#include "LevelFactory.h"

#include <tuple>

using std::tuple;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API RandomObjectFactory :
		public LevelFactory
	{
	public:
		RandomObjectFactory();
		~RandomObjectFactory();

		void AddAlternativeFactory(float probability, LevelFactory* alternativeFactory);

		// Generates children for the parent
		virtual list<Item*> GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation);

	private:
		float _totalProbability;
		list<tuple< float, LevelFactory*>> _alternativeFactories; // List of objects that might be created, the first element of the tuple is the probability of the object to be chosen, the second is factory to create the object
	};
}