#pragma once

#include <fstream>
#include <string>
#include <unordered_map>

#include "FloatExpression.h"
#include "Vector3.h"

using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::unordered_map;
using Math::FloatExpression;

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
		FloatExpression* Read(ifstream* stream, unordered_map<string, FloatExpression*>* previousExpressions);
		void Write(ofstream* stream, FloatExpression* expressionToWrite);

	protected:
		// Concrete read, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual FloatExpression* InternalRead(ifstream* stream, unordered_map<string, FloatExpression*>* previousExpressions) = 0;
		// Concrete write, has to be implemented by any class implementing FloatExpressionDataModel.
		virtual void InternalWrite(ofstream* stream, FloatExpression* expressionToWrite) = 0;

		static FloatExpression* GetFloatExpressionByName(string name, unordered_map<string, FloatExpression*>* previousExpressions);

	private:
		// Instance name of the float expression.
		string _name;
		// The float expression itself.
		FloatExpression* _expression;
	};
}