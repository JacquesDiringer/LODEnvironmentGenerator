#pragma once
#include "LevelFactoryDataModel.h"

namespace DataModel
{
	class RandomObjectFactoryDataModel :
		public LevelFactoryDataModel
	{
	public:
		RandomObjectFactoryDataModel();
		~RandomObjectFactoryDataModel();

	protected:
		virtual LevelFactory* InternalRead(ifstream* stream, unordered_map<string, LevelFactory*>* previousFactories);
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite);
	};
}