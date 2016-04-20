#pragma once
#include "LevelFactoryDataModel.h"
#include "Vector3.h"

using Math::Vector3;

namespace DataModel
{
	class VoxelFactoryDataModel :
		public LevelFactoryDataModel
	{
	public:
		VoxelFactoryDataModel();
		~VoxelFactoryDataModel();

	protected:
		virtual LevelFactory* InternalRead(ifstream* stream, map<string, LevelFactory*>* previousFactories);
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite);

	private:
		static Vector3 ReadVector3(ifstream* stream);
	};
}