#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include "LevelFactory.h"
#include "FloatExpression.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_map;

using Generator::LevelFactory;
using Math::FloatExpression;

namespace DataModel
{
	class LevelFactoryDataModel
	{
	public:
		LevelFactoryDataModel();
		~LevelFactoryDataModel();

		string GetName() { return _name; }
		LevelFactory* GetFactory() { return _factory; }

		// Generic read, performs common duties like reading the factory's instance name, and filling the previousFactories map.
		LevelFactory* Read(ifstream* stream, unordered_map<string, LevelFactory*>* previousFactories);
		void Write(ofstream* stream, LevelFactory* factoryToWrite);

		// Add a float expression to the float expression map.
		void AddFloatExpression(const string& name, FloatExpression* expression);
		void AddFloatExpression(unordered_map<string, FloatExpression*>* additionalMap);

	protected:
		// Virtual methods.

		// Concrete read, has to be implemented by any class implementing LevelFactoryDataModel.
		virtual LevelFactory* InternalRead(ifstream* stream, unordered_map<string, LevelFactory*>* previousFactories) = 0;
		// Concrete write, has to be implemented by any class implementing LevelFactoryDataModel.
		virtual void InternalWrite(ofstream* stream, LevelFactory* factoryToWrite) = 0;


		// Utility functions.

		// Fetches a factory according to its instance name, in the previously loaded factories.
		static LevelFactory* GetFactoryByName(const string& name, unordered_map<string, LevelFactory*>* previousFactories);


		// Fields.

		// Instance name of the factory.
		string _name;
		// The factory itself.
		LevelFactory* _factory;
		// A static map of the read float expressions at the beginnig of the file. Each type of factory data model has to able to access it.
		unordered_map<string, FloatExpression*>* _floatExpressions;
	};
}

