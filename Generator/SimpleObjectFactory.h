#pragma once
#include "LevelFactory.h"
#include "Item.h"
#include "SimpleObjectDisplayable.h"
#include "ParametricPlane.h"

#include <string>

using std::string;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API SimpleObjectFactory :
		public LevelFactory
	{
	public:
		SimpleObjectFactory();
		SimpleObjectFactory(const string& modelName, const string& textureName, float expansionDistance, const vector<Math::ParametricPlane*>& visibilityPlanes, bool andCondition, LevelFactory* subLevelFactory);
		~SimpleObjectFactory();

		// Generates children for the parent
		virtual void GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector);

	private:
		SimpleObjectDisplayable * _modelSimpleDisplayable;
		float _expansionDistance;
		// A vector of parametric planes that count as an additionnal condition to determine whether the sub level should be expanded or not.
		// These planes will contain parametrization in local object space.
		vector<Math::ParametricPlane*> _visibilityPlanes;
		// When true all visibility planes have to return true, when false only one visibility plane true is enough.
		bool _visibilityPlanesAndCondition;
		LevelFactory* _subLevelFactory;
	};


}