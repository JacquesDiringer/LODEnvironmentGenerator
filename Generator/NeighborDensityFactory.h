#pragma once
#include "LevelFactory.h"
#include "Vector3.h"
#include "FloatExpression.h"

#include <map>
#include <list>

using namespace Math;

using std::map;
using std::list;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	class GENERATOR_API NeighborDensityFactory :
		public LevelFactory
	{
		struct Condition
		{
			Vector3 LocalFetchCoordinates;
			bool ExpectedValue;
		};

		class Rule
		{
		public:
			Rule();
			Rule(LevelFactory* factory);
			~Rule();

			void AddCondition(Vector3 fetchCoordinates, bool expectedValue);
			bool operator==(const Rule &other);

			list<Condition*> GetConditions() const { return _conditionsList; }
			LevelFactory* GetFactory() const { return _factory; }

		private:
			LevelFactory* _factory;
			list<Condition*> _conditionsList;
		};

	public:
		NeighborDensityFactory();
		NeighborDensityFactory(Vector3 voxelSize, FloatExpression* densityExpression, bool isDomainLimited, float minimalDensity);
		~NeighborDensityFactory();

		// Generates children for the parent.
		virtual list<Item*> GenerateLevel(Item* parent, int childrenNumber, const Matrix4* futureTransformation);
		void AddRule(list<bool>conditions, LevelFactory* factory);
		void AddRule(Rule* newRule);

	private:
		// Dimension of one voxel block.
		// This will determine the density function fetch step as well as the children position.
		Vector3 _voxelSize;
		// When true, density fetches that happen to be outside of the domain will always return a density value of 0.
		// TODO: Implement the 0 density fetch when outside the domain.
		bool _isDomainLimited;
		// Density at which a voxel is considered not empty.
		float _minimalDensity;
		// A map of a set of 8 rules, and a LevelFactory.
		// The boolean array corresponds to the density requirement at each vertex of the evaluated voxel, the LevelFactory will give the items to return in case the rule is fullfilled.
		// List of rules, each giving fetching coordinates and condition, and the corresponding Factory if all conditions are met.
		list<Rule*> _rules;
		// Density mathematical expression.
		FloatExpression* _densityExpression;

	private:
		list<Item*> ComputeVoxel(Item * parent, int childrenNumber, const Matrix4* futureTransformation);
		float DensityFunction(const Vector3 fetchCoordinates);
	};
}
