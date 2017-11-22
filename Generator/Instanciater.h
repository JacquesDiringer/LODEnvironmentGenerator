#pragma once

#include <vector>

#include "Displayable.h"

using std::vector;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API Instanciater
	{
	public:
		Instanciater();
		~Instanciater();

		virtual void UpdateDisplayables(vector<Displayable*> toAdd, vector<Displayable*> toRemove) = 0;
	};
}