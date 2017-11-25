#pragma once
#include "LevelFactoryDataModel.h"

namespace DataModel
{
	class SimpleObjectFactoryDataModel :
		public LevelFactoryDataModel
	{
	public:
		SimpleObjectFactoryDataModel();
		~SimpleObjectFactoryDataModel();

	protected:
		virtual LevelFactory* InternalRead(ifstream* stream, unordered_map<string, LevelFactory*>* previousFactories);
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite);
	};
}
