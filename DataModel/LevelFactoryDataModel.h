#pragma once

#include <fstream>
#include <string>
#include <map>

#include "LevelFactory.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;

using Generator::LevelFactory;

#ifdef DATAMODEL_EXPORTS
#define DATAMODEL_API __declspec(dllexport)
#else
#define DATAMODEL_API __declspec(dllimport)
#endif

namespace DataModel
{
	class DATAMODEL_API LevelFactoryDataModel
	{
	public:
		LevelFactoryDataModel();
		~LevelFactoryDataModel();

		string GetName() { return _name; }
		LevelFactory* GetFactory() { return _factory; }

		LevelFactory* Read(ifstream* stream, map<string, LevelFactory*>* previousFactories);
		void Write(ofstream* stream, LevelFactory* factoryToWrite);

	protected:
		virtual LevelFactory* InternalRead(ifstream* stream, map<string, LevelFactory*>* previousFactories) = 0;
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite) = 0;

		string _name;
		LevelFactory* _factory;
	};
}

