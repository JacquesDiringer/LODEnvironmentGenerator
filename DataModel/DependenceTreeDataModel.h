#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "LevelFactory.h"
#include "LevelFactoryDataModel.h"
#include "FloatExpressionDataModel.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_map;
using std::unordered_set;

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
		LevelFactory* ReadFile(string filePath, unordered_set<string>& visitedFiles, unordered_map<string, LevelFactory*>& previousFactories, unordered_map<string, FloatExpression*>* previousExpressions);
		void ReadFloatExpression(std::ifstream &inputStream, unordered_map<string, FloatExpression*>* previousExpressions);
		LevelFactory* ReadFactories(std::ifstream &inputStream, unordered_set<string>& visitedFiles, unordered_map<string, LevelFactory*>& previousFactories);

		// Associates the type of a factory to factory data model type.
		unordered_map<string, LevelFactoryDataModel*> _factoriesDataModelMap;

		// Associates the type of a float expression to float expression data model type.
		unordered_map<string, FloatExpressionDataModel*> _floatExpressionsDataModelMap;
	};
}
