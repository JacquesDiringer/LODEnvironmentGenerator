#pragma once

#include "Vector3.h"

#ifdef GENERATOR_EXPORTS
#define GENERATOR_API __declspec(dllexport)
#else
#define GENERATOR_API __declspec(dllimport)
#endif

namespace Math
{
	/// Abstract class for mathematical expressions.
	/// This will handle expressions using the interpreter pattern.
	class GENERATOR_API FloatExpression
	{
	public:
		FloatExpression();
		~FloatExpression();

		/// Recursively evaluates the value of it's concrete FloatExpression implementations.
		virtual float Evaluate(Vector3 coordinates) =0;
	};
}