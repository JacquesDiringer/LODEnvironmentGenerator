// Generator.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Generator.h"


// This is an example of an exported variable
GENERATOR_API int nGenerator=0;

// This is an example of an exported function.
GENERATOR_API int fnGenerator(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see Generator.h for the class definition
CGenerator::CGenerator()
{
	return;
}
