#pragma once

#include <fstream>

#include "Vector3.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using Math::Vector3;

namespace DataModel
{
	class UtilityReaderWriter
	{
	public:
		UtilityReaderWriter();
		~UtilityReaderWriter();

		// Read a single line in the stream and interpret it as a float, stream will go the next line.
		static float ReadFloat(ifstream* stream);
		static bool ReadBool(ifstream* stream);
		static Vector3 ReadVector3(ifstream* stream);
	};
}