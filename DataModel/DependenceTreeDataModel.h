#pragma once

#include <fstream>
#include <string>
#include <map>;

#include "LevelFactory.h"
#include "LevelFactoryDataModel.h"
#include "FloatExpressionDataModel.h"

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
		// Associates the type of a factory to factory data model type.
		map<string, LevelFactoryDataModel*> _factoriesDataModelMap;

		// Associates the type of a float expression to float expression data model type.
		map<string, FloatExpressionDataModel*> _floatExpressionsDataModelMap;
	};
}
