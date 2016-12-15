#pragma once

#include <fstream>
#include <string>
#include <map>

#include "FloatExpression.h"
#include "Vector3.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;
using Math::FloatExpression;
using Math::Vector3;

namespace DataModel
{
	class FloatExpressionDataModel
	{
	public:
		FloatExpressionDataModel();
		~FloatExpressionDataModel();

		string GetName() { return _name; }
		FloatExpression* GetFloatExpression() { return _expression; }

		// Generic read, performs common duties like reading the float expression's instance name, and filling the previousExpressions map.
		FloatExpression* Read(ifstream* stream, map<string, FloatExpression*>* previousExpressions);
		void Write(ofstream* stream, FloatExpression* expressionToWrite);

	protected:
		// Concrete read, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual FloatExpression* InternalRead(ifstream* stream, map<string, FloatExpression*>* previousExpressions) = 0;
		// Concrete write, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual void InternalWrite(ofstream* stream, FloatExpression* expressionToWrite) = 0;

		static FloatExpression* GetFloatExpressionByName(string name, map<string, FloatExpression*>* previousExpressions);

		// Instance name of the float expression.
		string _name;
		// The float expression itself.
		FloatExpression* _expression;
	};
}