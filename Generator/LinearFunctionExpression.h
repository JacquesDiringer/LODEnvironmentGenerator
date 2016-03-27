#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	class GENERATOR_API LinearFunctionExpression :
		public FloatExpression
	{
	public:
		LinearFunctionExpression();
		LinearFunctionExpression(Vector3 ratios);
		~LinearFunctionExpression();

		virtual float Evaluate(Vector3 coordinates);

	private:
		Vector3 _ratios;
	};

	}