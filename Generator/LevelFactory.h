#pragma once

#include "Matrix4.h"

#include <vector>
#include <memory>

using Math::Matrix4;

using std::vector;
using std::shared_ptr;
using std::weak_ptr;

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
		virtual void GenerateLevel(weak_ptr<Item> parent, int childrenNumber, const Matrix4& futureTransformation, const Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector) = 0;
	};
}