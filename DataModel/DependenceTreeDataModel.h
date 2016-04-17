#pragma once

#include <fstream>
#include <string>
#include <map>;

#include "LevelFactory.h"
#include "LevelFactoryDataModel.h"

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
	class DATAMODEL_API DependenceTreeDataModel
	{
	public:
		DependenceTreeDataModel();
		~DependenceTreeDataModel();

		// Reads a dependence tree file and returns the root node factory.
		LevelFactory* Read(string filePath);

	private:
		// Associates the name of a factory to factory data model
		map<string, LevelFactoryDataModel*> _factoriesDataModelMap;
	};
}
