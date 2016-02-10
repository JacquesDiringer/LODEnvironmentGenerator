#include "stdafx.h"
#include "RandomObjectFactory.h"

#include <random>


namespace Generator
{
	RandomObjectFactory::RandomObjectFactory()
	{
		_totalProbability = 0;
		_alternativeFactories = list<tuple<float, LevelFactory*>>();
	}


	RandomObjectFactory::~RandomObjectFactory()
	{
	}

	void RandomObjectFactory::AddAlternativeFactory(float probability, LevelFactory* alternativeFactory)
	{
		if (alternativeFactory != NULL)
		{
			_alternativeFactories.push_back(std::make_tuple(probability, alternativeFactory));
		}
		_totalProbability += probability;
	}

	list<Item*> RandomObjectFactory::GenerateLevel(Item* parent, int childrenNumber)
	{
		list<Item*> result = list<Item*>();

		std::srand((parent->GetId() + childrenNumber) * (parent->GetId() + childrenNumber) * 100);

		int newSeed = std::rand();

		std::srand(newSeed);

		//float randomNumber = ((float)(std::rand() % 100) / 100.0f) * _totalProbability; // a random number in the range [0, _totalProbability]
		float randomNumber = ((float)(std::rand()) / (float)(RAND_MAX)) * _totalProbability; // a random number in the range [0, _totalProbability]
		// TODO: find a better way to generate a random number

		float probabilityCounter = 0;

		for each (tuple< float, LevelFactory*> currentTuple in _alternativeFactories)
		{
			probabilityCounter += std::get<0>(currentTuple);
			if (probabilityCounter > randomNumber)
			{
				LevelFactory* currentFactory = std::get<1>(currentTuple);
				return currentFactory->GenerateLevel(parent, childrenNumber);
			}
		}

		// In this case, the "empty" object was chosen, we return an Item containing no displayable nor sub level factory
		// The reason to do this instead of simply returning an empty list is that we want to keep the link with the father, otherwise the father won't be recreated  when the Item is "upped"
		Item* simpleObject = new Item(Matrix4::Identity(), parent, 0.0f, NULL, NULL);
		result.push_back(simpleObject);
		return result;
	}
}