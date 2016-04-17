#pragma once

#include <fstream>
#include <string>

#include "LevelFactory.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

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
		static LevelFactory* Read(string filePath);
	};

}
