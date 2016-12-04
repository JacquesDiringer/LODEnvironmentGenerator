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
}