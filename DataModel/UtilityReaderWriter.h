#pragma once

#include <fstream>

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;

namespace DataModel
{
	class UtilityReaderWriter
	{
	public:
		UtilityReaderWriter();
		~UtilityReaderWriter();

		// Read a single line in the stream and interpret it as a float, stream will go the next line.
		static float ReadFloat(ifstream* stream);
	};
}