#pragma once
#include "LevelFactoryDataModel.h"

namespace DataModel
{
	class ArrayFactoryDataModel :
		public LevelFactoryDataModel
	{
	public:
		ArrayFactoryDataModel();
		~ArrayFactoryDataModel();

	protected:
		virtual LevelFactory* InternalRead(ifstream* stream, map<string, LevelFactory*>* previousFactories);
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite);
	};
}