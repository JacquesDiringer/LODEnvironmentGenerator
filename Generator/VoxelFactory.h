#pragma once
#include "LevelFactory.h"
#include "Vector3.h"
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
	class GENERATOR_API VoxelFactory :
		public LevelFactory
	{
	public:
		VoxelFactory();
		VoxelFactory(Vector3 voxelSize, Vector3 domainSize, bool isDomainLimited, float minimalDensity);
		~VoxelFactory();

		// Generates children for the parent.
		virtual list<Item*> GenerateLevel(Item* parent, int childrenNumber);
		void AddRule(bool const conditions[8], LevelFactory* factory);
		void AddRule(list<bool>conditions, LevelFactory* factory);

	private:
		// Dimension of one voxel block.
		// This will determine the density function fetch step as well as the children position.
		Vector3 _voxelSize;
		// Dimension of the domain that will spawn children.
		Vector3 _domainSize;
		// When true, density fetches that happen to be outside of the domain will always return a density value of 0.
		// TODO: Implement the 0 density fetch when outside the domain.
		bool _isDomainLimited;
		// Density at which a voxel is considered not empty.
		float _minimalDensity;
		// A map of a set of 8 rules, and a LevelFactory.
		// The boolean array corresponds to the density requirement at each vertex of the evaluated voxel, the LevelFactory will give the items to return in case the rule is fullfilled.
		map<list<bool>, LevelFactory*> _rules;

	private:
		list<Item*> ComputeVoxel(Item * parent, int childrenNumber, Vector3 localCoordinates);
		float DensityFunction(const Vector3 fetchCoordinates);
	};
}
