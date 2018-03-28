#pragma once
#include "FloatExpression.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	class GENERATOR_API CoordinatesTranslationExpression :
		public FloatExpression
	{
	public:
		CoordinatesTranslationExpression(FloatExpression* childExpression, Math::Vector3 translation);
		~CoordinatesTranslationExpression();

		/// Recursively evaluates the value of it's concrete FloatExpression implementations.
		float Evaluate(Math::Vector3 coordinates);

	private:
		FloatExpression* _childExpression;
		Math::Vector3 _translation;
	};

}