#pragma once

#include <memory>

#include "LevelFactory.h"
#include "Matrix4.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API TransformationFactory :
		public LevelFactory
	{
	public:
		TransformationFactory();
		TransformationFactory(LevelFactory* factory, Math::Matrix4 transformation);
		~TransformationFactory();

		// Generates children for the parent
		virtual void GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector);

	private:
		LevelFactory* _factory;
		Math::Matrix4 _transformation;
	};


}