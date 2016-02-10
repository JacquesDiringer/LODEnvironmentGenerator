#pragma once

#include <list>

#include "Displayable.h"

using std::list;

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

		virtual void UpdateDisplayables(list<Displayable*> toAdd, list<Displayable*> toRemove) = 0;
	};
}