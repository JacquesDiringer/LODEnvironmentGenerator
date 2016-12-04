#pragma once
#include "LevelFactoryDataModel.h"
#include "Vector3.h"

using Math::Vector3;

namespace DataModel
{
	class NeighborDensityFactoryDataModel :
		public LevelFactoryDataModel
	{
	public:
		NeighborDensityFactoryDataModel();
		~NeighborDensityFactoryDataModel();

	protected:
		virtual LevelFactory* InternalRead(ifstream* stream, map<string, LevelFactory*>* previousFactories);
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite);
	};
}