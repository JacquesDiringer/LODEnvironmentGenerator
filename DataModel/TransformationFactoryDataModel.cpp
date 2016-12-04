#include "stdafx.h"
#include "TransformationFactoryDataModel.h"

#include "TransformationFactory.h"
#include "UtilityReaderWriter.h"

using std::getline;
using Generator::TransformationFactory;


namespace DataModel
{
	TransformationFactoryDataModel::TransformationFactoryDataModel()
	{
		_floatExpressions = new map<string, FloatExpression*>();
	}

	TransformationFactoryDataModel::~TransformationFactoryDataModel()
	{
	}

	LevelFactory * TransformationFactoryDataModel::InternalRead(ifstream * stream, map<string, LevelFactory*>* previousFactories)
	{
		// Name of the subLevelFactory to be read in the file.
		string subLevelFactoryName;
		// Get the string name of the sublevel factory.
		getline(*stream, subLevelFactoryName);
		// Get the sublevel factory according to its name, if it exist.
		LevelFactory* subLevelFactory = GetFactoryByName(subLevelFactoryName, previousFactories);

		// The sublevel has to exist.
		if (subLevelFactory == NULL)
		{
			throw new std::invalid_argument("A transformation factory should always have a sublevel.");
		}

		// Descriptor of the matrix constructor to read and use.
		string matrixConstructor;
		// Get the matrix constructor.
		getline(*stream, matrixConstructor);

		// Final transformation matrix.
		Matrix4 transformation;

		if (matrixConstructor == "Matrix")
		{
			transformation = ReadMatrix4(stream);
		}
		else if(matrixConstructor == "YRotation")
		{
			transformation = ReadYRotation(stream);
		}
		else if (matrixConstructor == "Translation")
		{
			transformation = ReadTranslation(stream);
		}
		else
		{
			throw new std::exception("Invalid constructor specified.");
		}

		_factory = new TransformationFactory(subLevelFactory, transformation);
		return _factory;
	}

	void TransformationFactoryDataModel::InternalWrite(ofstream * stream, LevelFactory * factoryToWrite)
	{
		throw std::exception("Not implemented");
	}
	Matrix4 TransformationFactoryDataModel::ReadMatrix4(ifstream * stream)
	{
		// Read the 16 matrix values.
		float matrixParameters[16];

		for (int i = 0; i < 16; i++)
		{
			matrixParameters[i] = UtilityReaderWriter::ReadFloat(stream);
		}

		// Create and return the matrix.
		return Matrix4(matrixParameters[0], matrixParameters[1], matrixParameters[2], matrixParameters[3],
			matrixParameters[4], matrixParameters[5], matrixParameters[6], matrixParameters[7],
			matrixParameters[8], matrixParameters[9], matrixParameters[10], matrixParameters[11],
			matrixParameters[12], matrixParameters[13], matrixParameters[14], matrixParameters[15]);
	}
	Matrix4 TransformationFactoryDataModel::ReadYRotation(ifstream * stream)
	{
		// Get the rotation value.
		float rotation = UtilityReaderWriter::ReadFloat(stream);

		// Create and return the matrix.
		return Matrix4::CreateRotationY(rotation);
	}
	Matrix4 TransformationFactoryDataModel::ReadTranslation(ifstream * stream)
	{
		// The 3 floats for the described translation.
		float translationParameters[3];

		// Stores the current parameter being read.
		string currentParameter;

		// Read the 3 values.
		for (int i = 0; i < 3; i++)
		{
			translationParameters[i] = UtilityReaderWriter::ReadFloat(stream);
		}

		// Create and return the matrix.
		return Matrix4::CreateTranslation(Vector3(	translationParameters[0],
													translationParameters[1],
													translationParameters[2]));
	}
}