#pragma once
#include "LevelFactoryDataModel.h"
#include "NeighborDensityFactory.h"
#include "Vector3.h"

using Generator::NeighborDensityFactory;
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

	private:
		static void Read8FetchRule(ifstream * stream, map<string, LevelFactory*>* previousFactories, NeighborDensityFactory* factory);
		static void ReadCustomRule(ifstream * stream, map<string, LevelFactory*>* previousFactories, NeighborDensityFactory* factory);
	};
}