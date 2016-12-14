#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	// Represents an Axis Aligned Box Expression.
	class GENERATOR_API AABExpression :
		public FloatExpression
	{
	public:
		AABExpression();
		AABExpression(Vector3 boxOrigin, Vector3 boxDimensions, bool centered);
		~AABExpression();

		virtual float Evaluate(Vector3 coordinates);

	private:
		Vector3 _boxOrigin, _boxDimensions;
		bool _centered;
	};
}