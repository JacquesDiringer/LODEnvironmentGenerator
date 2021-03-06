#pragma once

#include "Matrix4.h"

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::weak_ptr;
using std::make_shared;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class Item;

	class GENERATOR_API LevelFactory
	{
	public:
		LevelFactory();
		~LevelFactory();

		// Generates children for the parent
		virtual void GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector) = 0;
	};
}