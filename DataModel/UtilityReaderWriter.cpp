#include "stdafx.h"
#include "UtilityReaderWriter.h"

#include <iostream>
#include <string>

namespace DataModel
{
	UtilityReaderWriter::UtilityReaderWriter()
	{
	}


	UtilityReaderWriter::~UtilityReaderWriter()
	{
	}

	float UtilityReaderWriter::ReadFloat(ifstream * stream)
	{
		string currentLine;
		getline(*stream, currentLine);

		return std::stof(currentLine);
	}
	bool UtilityReaderWriter::ReadBool(ifstream * stream)
	{
		string currentLine;
		getline(*stream, currentLine);

		return currentLine == "true" || currentLine == "1";
	}

	Math::Vector3 UtilityReaderWriter::ReadVector3(ifstream* stream)
	{
		string currentLine;

		// Get the X component.
		float voxelSizeX = UtilityReaderWriter::ReadFloat(stream);

		// Get the Y component.
		float voxelSizeY = UtilityReaderWriter::ReadFloat(stream);

		// Get the Z component.
		float voxelSizeZ = UtilityReaderWriter::ReadFloat(stream);

		// Combine them into the final Vector3.
		return Math::Vector3(voxelSizeX, voxelSizeY, voxelSizeZ);
	}
}