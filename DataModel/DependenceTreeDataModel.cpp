#include "stdafx.h"
#include "DependenceTreeDataModel.h"

#include "LevelFactoryDataModel.h"
#include "SimpleObjectFactoryDataModel.h"

#include <map>;

#include<iostream>

using std::map;

namespace DataModel
{
	DependenceTreeDataModel::DependenceTreeDataModel()
	{
	}


	DependenceTreeDataModel::~DependenceTreeDataModel()
	{
	}

	LevelFactory * DependenceTreeDataModel::Read(string filePath)
	{
		map<string, LevelFactory*>* previousFactories = new map<string, LevelFactory*>();
		LevelFactory* lastFactory;

		ifstream inputStream(filePath, ifstream::in);

		if (inputStream)
		{
			string currentLine;

			while (std::getline(inputStream, currentLine))
			{
				std::cout << "Line : " << currentLine << std::endl;

				if (currentLine.length() > 0)
				{
					LevelFactoryDataModel* currentFactoryDataModel = new SimpleObjectFactoryDataModel;
					lastFactory = currentFactoryDataModel->Read(&inputStream, previousFactories);
				}
			}
		}
		else
		{
			throw new std::invalid_argument("File not found.");
		}

		return lastFactory;
	}

}