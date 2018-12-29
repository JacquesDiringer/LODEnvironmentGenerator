#pragma once
#include "LevelFactory.h"
#include "Vector3.h"
#include "FloatExpression.h"

#include <vector>

using std::vector;

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Generator
{
	struct Condition
	{
		Math::Vector3 LocalFetchCoordinates;
		bool ExpectedValue;
	};

	class GENERATOR_API Rule
	{
	public:
		Rule();
		Rule(LevelFactory* factory);
		~Rule();

		void AddCondition(Math::Vector3 fetchCoordinates, bool expectedValue);
		bool operator==(const Rule &other);

		const vector<Condition*>& GetConditions() const { return _conditionsList; }
		LevelFactory* GetFactory() const { return _factory; }

	private:
		LevelFactory* _factory;
		vector<Condition*> _conditionsList;
	};

	class GENERATOR_API NeighborDensityFactory :
		public LevelFactory
	{

	public:
		NeighborDensityFactory();
		NeighborDensityFactory(Math::Vector3 voxelSize, Math::FloatExpression* densityExpression, float minimalDensity);
		~NeighborDensityFactory();

		// Generates children for the parent.
		virtual void GenerateLevel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector);
		void AddRule(vector<bool>conditions, LevelFactory* factory);
		void AddRule(Rule* newRule);
		void SetDefaultFactory(LevelFactory* default) { _defaultFactory = default; }

	private:
		// Dimension of one voxel block.
		// This will determine the density function fetch step as well as the children position.
		Math::Vector3 _voxelSize;
		// Density at which a voxel is considered not empty.
		float _minimalDensity;
		// A map of a set of 8 rules, and a LevelFactory.
		// The boolean array corresponds to the density requirement at each vertex of the evaluated voxel, the LevelFactory will give the items to return in case the rule is fullfilled.
		// List of rules, each giving fetching coordinates and condition, and the corresponding Factory if all conditions are met.
		vector<Rule*> _rules;
		// Density mathematical expression.
		Math::FloatExpression* _densityExpression;

		// Factory used by default when no rule matches.
		LevelFactory* _defaultFactory;

	private:
		void ComputeVoxel(shared_ptr<Item> parent, int childrenNumber, const Math::Matrix4& futureTransformation, const Math::Matrix4& worldMatrix, vector<shared_ptr<Item>>* itemVector);
		float DensityFunction(const Math::Vector3 fetchCoordinates);
		Rule* ComputeQuarterRotatedRue(Rule* originalRule, int rotationCount);
	};
}
