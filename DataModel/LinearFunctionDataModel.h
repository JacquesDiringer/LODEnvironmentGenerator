#pragma once
#include "FloatExpressionDataModel.h"

namespace DataModel
{
	class LinearFunctionDataModel :
		public FloatExpressionDataModel
	{
	public:
		LinearFunctionDataModel();
		~LinearFunctionDataModel();

	protected:
		// Concrete read, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual FloatExpression* InternalRead(ifstream* stream, map<string, FloatExpression*>* previousExpressions);
		// Concrete write, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual void InternalWrite(ofstream* stream, FloatExpression* expressionToWrite);
	};
}