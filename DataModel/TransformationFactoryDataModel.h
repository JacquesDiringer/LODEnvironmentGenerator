#pragma once
#include "LevelFactoryDataModel.h"

#include "Matrix4.h"

#ifdef DATAMODEL_EXPORTS
#define DATAMODEL_API __declspec(dllexport)
#else
#define DATAMODEL_API __declspec(dllimport)
#endif

namespace DataModel
{
	class DATAMODEL_API TransformationFactoryDataModel :
		public LevelFactoryDataModel
	{
	public:
		TransformationFactoryDataModel();
		~TransformationFactoryDataModel();

	protected:
		virtual LevelFactory* InternalRead(ifstream* stream, unordered_map<string, LevelFactory*>* previousFactories);
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite);

	private:
		Math::Matrix4 ReadMatrix4(ifstream* stream);
		Math::Matrix4 ReadYRotation(ifstream* stream);
		Math::Matrix4 ReadTranslation(ifstream* stream);
	};
}

