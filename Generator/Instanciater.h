#pragma once

#include <vector>
#include <memory>

#include "Displayable.h"

using std::vector;
using std::shared_ptr;

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

		virtual void UpdateDisplayables(const vector<shared_ptr<Displayable>>& toAdd, const vector<shared_ptr<Displayable>>& toRemove) = 0;
	};
}