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

namespace DataModel
{
	class LevelFactoryDataModel
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

		LevelFactory* GetFactoryByName(string name, map<string, LevelFactory*>* previousFactories);

		string _name;
		LevelFactory* _factory;
	};
}

