#pragma once
#include "FloatExpressionDataModel.h"
namespace DataModel
{
	class MultiplicationDataModel :
		public FloatExpressionDataModel
	{
	public:
		MultiplicationDataModel();
		~MultiplicationDataModel();

	protected:
		// Concrete read, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual FloatExpression* InternalRead(ifstream* stream, map<string, FloatExpression*>* previousExpressions);
		// Concrete write, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual void InternalWrite(ofstream* stream, FloatExpression* expressionToWrite);
	};
}